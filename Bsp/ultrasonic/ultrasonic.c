#ifdef __cplusplus
extern "C" {
#endif

/* ANCHOR - 头文件包含 */

#include "ultrasonic.h"
#include "tim.h"

/* ANCHOR - 全局变量定义 */

/**
 * *****************************************************************************
 * @note - TIM3CH3_CAPTURE_STA 变量 (Bit0-15): 用于存放捕获状态
 * @note    - Bit7: 表示脉宽测量的整个过程是否完成 1:完成 0:未完成
   @note    - Bit6: 表示是否捕获到上升沿 1:捕获到了 0:没有捕获到
   @note    - Bit0-5: 表示高电平期间发生的定时器更新中断次数
 * *****************************************************************************
 */
u16 TIM3CH3_CAPTURE_STA;
/**
 * *****************************************************************************
 * @note - TIM3CH3_CAPTURE_VAL 变量 (Bit0-15): 用于存放捕获的数值
 * *****************************************************************************
 */
u16 TIM3CH3_CAPTURE_VAL;

/* ANCHOR - 公共函数定义 */

/**
 * *****************************************************************************
 * @brief 超声波接收回波函数
 * @return u32 距离
 * *****************************************************************************
 */
u32 Read_Distance(void)
{
    u32 Distance = 0;

    /* 触发超声波模块发射超声波 */
    Trigger_SET();
    HAL_Delay(1);
    Trigger_RESET();

    if (TIM3CH3_CAPTURE_STA & 0X80)
    {
        Distance = TIM3CH3_CAPTURE_STA & 0X3F;
        Distance *= 65536;               /* 溢出时间总和 */
        Distance += TIM3CH3_CAPTURE_VAL; /* 得到总的高电平时间 */
        /* 时间*声速/2(来回) 一个计数 0.001ms (预分频系数 72, 预分频设置值 72-1) */
        Distance = Distance * 170 / 1000;
        TIM3CH3_CAPTURE_STA = 0; /* 开启下一次捕获 */
    }
    return Distance;
}

/**
 * *****************************************************************************
 * @brief 进入定时器 3 中断后, 在定时器 3 中断里判断出是捕获中断, 然后进入此回调函数
 * @param [in] htim 定时器句柄 
 * *****************************************************************************
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef* htim) //捕获中断发生时执行
{
    if (htim == &htim3)
    {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
        {
            if ((TIM3CH3_CAPTURE_STA & 0X80) == 0) /* 还未成功捕获 */
            {
                if (TIM3CH3_CAPTURE_STA & 0X40) /* 捕获到一个下降沿 */
                {
                    TIM3CH3_CAPTURE_STA |=
                        0X80; /* 标记成功捕获到一次高电平脉宽 */
                    TIM3CH3_CAPTURE_VAL = HAL_TIM_ReadCapturedValue(
                        &htim3, TIM_CHANNEL_3); /* 获取当前的捕获值 */
                    __HAL_TIM_DISABLE(&htim3);  /* 禁用定时器 3 */
                    TIM_RESET_CAPTUREPOLARITY(
                        &htim3, TIM_CHANNEL_3); /* 清除原来的设置 */
                    TIM_SET_CAPTUREPOLARITY(
                        &htim3,
                        TIM_CHANNEL_3,
                        TIM_ICPOLARITY_RISING); /* 配置 TIM3 通道 3 上升沿捕获 */
                    __HAL_TIM_ENABLE(&htim3); /* 使能定时器 3 */
                }
                else /* 还未开始,第一次捕获上升沿 */
                {
                    TIM3CH3_CAPTURE_STA = 0; /* 清空 */
                    TIM3CH3_CAPTURE_VAL = 0;
                    TIM3CH3_CAPTURE_STA |= 0X40; /* 标记捕获到了上升沿 */

                    __HAL_TIM_DISABLE(&htim3);        /* 关闭定时器 3 */
                    __HAL_TIM_SET_COUNTER(&htim3, 0); /* 计数器 CNT 置 0 */
                    TIM_RESET_CAPTUREPOLARITY(
                        &htim3, TIM_CHANNEL_3); /* 清除原来的设置 */
                    TIM_SET_CAPTUREPOLARITY(
                        &htim3,
                        TIM_CHANNEL_3,
                        TIM_ICPOLARITY_FALLING); /* 定时器 3 通道 3 设置为下降沿捕获 */
                    __HAL_TIM_ENABLE(&htim3); /* 使能定时器 3 */
                }
            }
        }
    }
}

/**
 * *****************************************************************************
 * @brief 定时器更新中断 (计数溢出) 中断处理回调函数, 该函数在 HAL_TIM_IRQHandler 中会被调用
 * @param [in] htim 
 * *****************************************************************************
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
    if (htim == &htim3)
    {
        if ((TIM3CH3_CAPTURE_STA & 0X80) == 0)
        {
            if (TIM3CH3_CAPTURE_STA & 0X40) /* 已经捕获到高电平了 */
            {
                if ((TIM3CH3_CAPTURE_STA & 0X3F) == 0X3F) /* 高电平太长了 */
                {
                    TIM3CH3_CAPTURE_STA |= 0X80; /* 标记成功捕获了一次 */
                    TIM3CH3_CAPTURE_VAL = 0XFFFF;
                }
                else
                {
                    TIM3CH3_CAPTURE_STA++;
                }
            }
        }
    }
}

#ifdef __cplusplus
}
#endif
