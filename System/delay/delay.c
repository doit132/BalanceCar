#ifdef __cplusplus
extern "C" {
#endif

/* ANCHOR - 头文件包含 */
#include "delay.h"

/* ANCHOR - 局部全局变量 */
static u8 fac_us = 0; /* us 延时倍乘数 */
static u16 fac_ms = 0; /* ms 延时倍乘数, 在 ucos 下, 代表每个节拍的 ms 数 */

/* ANCHOR - 函数定义 */
/**
 * @brief 初始化延迟函数
 * 当使用 OS 的时候, 此函数会初始化 OS 的时钟节拍
 * SYSTICK 的时钟固定为 HCLK 时钟的 1/8
 * SYSCLK: 系统时钟
 */
void delay_init(void)
{
#if SYSTEM_SUPPORT_OS //如果需要支持 OS.
    u32 reload;
#endif
    HAL_SYSTICK_CLKSourceConfig(RCC_SYSCLK_DIV8); // 选择外部时钟 HCLK/8
    fac_us = SystemCoreClock / 8000000;           //为系统时钟的 1/8
#if SYSTEM_SUPPORT_OS                             //如果需要支持 OS.
    reload = SystemCoreClock / 8000000; //每秒钟的计数次数 单位为 M
    /* 
        根据 delay_ostickspersec 设定溢出时间
        reload 为 24 位寄存器, 最大值: 16777216, 在 72M 下, 约合 1.86s 左右 
    */
    reload *= 1000000 / delay_ostickspersec;
    fac_ms = 1000 / delay_ostickspersec; //代表 OS 可以延时的最少单位

    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk; //开启 SYSTICK 中断
    SysTick->LOAD = reload; //每1/delay_ostickspersec秒中断一次
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //开启 SYSTICK

#else
    fac_ms = (u16)fac_us * 1000; // 非 OS 下, 代表每个 ms 需要的 systick 时钟数
#endif
}

#if SYSTEM_SUPPORT_OS // 如果需要支持 OS
/**
 * @brief 延时nus
 * 
 * @param nus nus 为要延时的 us 数
 */
void delay_us(u32 nus)
{
    u32 ticks;
    u32 told, tnow, tcnt = 0;
    u32 reload = SysTick->LOAD; //LOAD 的值
    ticks = nus * fac_us;       //需要的节拍数
    tcnt = 0;
    delay_osschedlock(); //阻止 OS 调度, 防止打断 us 延时
    told = SysTick->VAL; //刚进入时的计数器值
    while (1)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            //这里注意一下 SYSTICK 是一个递减的计数器就可以了.
            if (tnow < told)
                tcnt += told - tnow;
            else
                tcnt += reload - tnow + told;
            told = tnow;
            if (tcnt >= ticks)
                break; //时间超过/等于要延迟的时间, 则退出.
        }
    };
    delay_osschedunlock(); //恢复 OS 调度
}

/**
 * @brief 延时 nms
 * 
 * @param nms 要延时的 ms 数
 */
void delay_ms(u16 nms)
{
    //如果 OS 已经在跑了, 并且不是在中断里面 (中断里面不能任务调度)
    if (delay_osrunning && delay_osintnesting == 0)
    {
        if (nms >= fac_ms) //延时的时间大于 OS 的最少时间周期
        {
            delay_ostimedly(nms / fac_ms); //OS 延时
        }
        nms %= fac_ms; //OS 已经无法提供这么小的延时了, 采用普通方式延时
    }
    delay_us((u32)(nms * 1000)); //普通方式延时
}
#else // 不用 OS 时
/**
 * @brief 延时nus
 * 
 * @param nus nus 为要延时的 us 数
 */
void delay_us(u32 nus)
{
    u32 temp;
    SysTick->LOAD = nus * fac_us;             /* 时间加载 */
    SysTick->VAL = 0x00;                      /* 清空计数器 */
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; /* 开始倒数 */
    do
    {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16))); /* 等待时间到达 */
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;      /* 关闭计数器 */
    SysTick->VAL = 0X00;                            /* 清空计数器 */
}

/**
 * @brief 延时 nms
 * 
 * @param nms 要延时的 ms 数
 * @note 
 * 注意 nms 的范围
 * SysTick->LOAD为24位寄存器,所以,最大延时为: nms<=0xffffff*8*1000/SYSCLK
 * SYSCLK 单位为 Hz, nms 单位为 ms, 对 72M 条件下, nms<=1864
 */
void delay_ms(volatile u16 nms)
{
    u32 temp;
    SysTick->LOAD = (u32)nms * fac_ms; //时间加载 (SysTick->LOAD 为 24bit)
    SysTick->VAL = 0x00;               //清空计数器
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //开始倒数
    do
    {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16))); //等待时间到达
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;      //关闭计数器
    SysTick->VAL = 0X00;                            //清空计数器
}
#endif

#ifdef __cplusplus
}
#endif
