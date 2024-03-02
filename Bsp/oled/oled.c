
#ifdef __cplusplus
extern "C" {
#endif

/* ANCHOR - 头文件包含 */

#include "oled.h"
#include "font.h"

/* ANCHOR - 私有全局变量定义 */

static u8 OLED_GRAM[128][8]; /* 128*64 分辨率 */

/* ANCHOR - 私有函数定义 */

/**
 * *****************************************************************************
 * @brief 求 m 的 n 次方的函数
 * @param [in] m 底数
 * @param [in] n 次方数
 * @return u32
 * *****************************************************************************
 */
static u32 OLED_Pow(u8 m, u8 n)
{
    u32 result = 1;
    while (n--)
        result *= m;
    return result;
}

/* ANCHOR - 公共函数定义 */

/**
 * *****************************************************************************
 * @brief 刷新 OLED 屏幕
 * *****************************************************************************
 */
void OLED_Refresh_Gram(void)
{
    u8 i, n;
    for (i = 0; i < 8; i++)
    {
        /* 设置页地址（0~7） */
        OLED_WR_Byte(0xb0 + i, OLED_CMD);
        /* 设置显示位置—列低地址 */
        OLED_WR_Byte(0x00, OLED_CMD);
        /* 设置显示位置—列高地址 */
        OLED_WR_Byte(0x10, OLED_CMD);
        for (n = 0; n < 128; n++)
            OLED_WR_Byte(OLED_GRAM[n][i], OLED_DATA);
    }
}

/**
 * *****************************************************************************
 * @brief 向 OLED 写入一个字节
 * @param [in] dat 要写入的数据/命令
 * @param [in] cmd 数据/命令标志 0: 表示命令, 1: 表示数据
 * *****************************************************************************
 */
void OLED_WR_Byte(u8 dat, u8 cmd)
{
    u8 i;

    /* 1. 决定是发送命令还是数据 */
    if (cmd)
    {
        OLED_DC_Set();
    }
    else
    {
        OLED_DC_Clr();
    }

    /* 2. SPI 写一个字节  */
    for (i = 0; i < 8; i++)
    {
        OLED_SCLK_Clr();
        if (dat & 0x80)
        {
            OLED_SDA_Set();
        }
        else
        {
            OLED_SDA_Clr();
        }
        OLED_SCLK_Set();
        dat <<= 1;
    }
    OLED_DC_Set();
}
/**
 * *****************************************************************************
 * @brief 开启 OLED 显示
 * *****************************************************************************
 */
void OLED_Display_On(void)
{
    OLED_WR_Byte(0X8D, OLED_CMD); //SET DCDC 命令
    OLED_WR_Byte(0X14, OLED_CMD); //DCDC ON
    OLED_WR_Byte(0XAF, OLED_CMD); //DISPLAY ON
}

/**
 * *****************************************************************************
 * @brief 关闭 OLED 显示
 * *****************************************************************************
 */
void OLED_Display_Off(void)
{
    OLED_WR_Byte(0X8D, OLED_CMD); //SET DCDC命令
    OLED_WR_Byte(0X10, OLED_CMD); //DCDC OFF
    OLED_WR_Byte(0XAE, OLED_CMD); //DISPLAY OFF
}

/**
 * *****************************************************************************
 * @brief 清屏功能, 清屏后, 整个屏幕是黑色的, 和没有亮起来的一样 
 * *****************************************************************************
 */
void OLED_Clear(void)
{
    u8 i, n;
    for (i = 0; i < 8; i++)
        for (n = 0; n < 128; n++)
            OLED_GRAM[n][i] = 0X00;
    OLED_Refresh_Gram(); //更新显示
}

/**
 * *****************************************************************************
 * @brief 画点
 * @param [in] x 起点横坐标 0-127
 * @param [in] y 起点纵坐标 0-63
 * @param [in] mode 1: 填充 0: 清空
 * *****************************************************************************
 */
void OLED_DrawPoint(u8 x, u8 y, u8 mode)
{
    u8 pos, bx, temp = 0;
    if (x > 127 || y > 63)
        return; //超出范围了.
    pos = 7 - y / 8;
    bx = y % 8;
    temp = 1 << (7 - bx);
    if (mode)
        OLED_GRAM[x][pos] |= temp;
    else
        OLED_GRAM[x][pos] &= ~temp;
}

/**
 * *****************************************************************************
 * @brief 在指定位置显示一个字符,包括部分字符
 * @param [in] x 起点横坐标 0-127
 * @param [in] y 起点纵坐标 0-63
 * @param [in] chr 要显示的字符
 * @param [in] size 字体大小
 * @param [in] mode 0: 反白显示, 1: 正常显示
 * *****************************************************************************
 */
void OLED_ShowChar(u8 x, u8 y, u8 chr, u8 size, u8 mode)
{
    u8 temp, i, j;
    u8 y0 = y;
    chr = chr - ' '; /* 得到偏移后的值 */
    for (i = 0; i < size; i++)
    {
        if (size == 12)
            temp = oled_asc2_1206[chr][i]; /* 调用 1206 字体 */
        else
            temp = oled_asc2_1608[chr][i]; /* 调用 1608 字体 */
        for (j = 0; j < 8; j++)
        {
            if (temp & 0x80)
                OLED_DrawPoint(x, y, mode);
            else
                OLED_DrawPoint(x, y, !mode);
            temp <<= 1;
            y++;
            if ((y - y0) == size)
            {
                y = y0;
                x++;
                break;
            }
        }
    }
}

/**
 * *****************************************************************************
 * @brief 显示 2 个数字
 * @param [in] x 起点横坐标 0-127
 * @param [in] y 起点纵坐标 0-63
 * @param [in] num 显示的数字
 * @param [in] len 数字的位数
 * @param [in] size 字体大小
 * *****************************************************************************
 */
void OLED_ShowNumber(u8 x, u8 y, u32 num, u8 len, u8 size)
{
    u8 t, temp;
    u8 enshow = 0;
    for (t = 0; t < len; t++)
    {
        temp = (num / OLED_Pow(10, len - t - 1)) % 10;
        if (enshow == 0 && t < (len - 1))
        {
            if (temp == 0)
            {
                OLED_ShowChar(x + (size / 2) * t, y, ' ', size, 1);
                continue;
            }
            else
                enshow = 1;
        }
        OLED_ShowChar(x + (size / 2) * t, y, temp + '0', size, 1);
    }
}

/**
 * *****************************************************************************
 * @brief 显示字符串
 * @param [in] x 起点横坐标 0-127
 * @param [in] y 起点纵坐标 0-63
 * @param [in] p 字符串起始地址
 * @note - 显示的字体是 12*6, 一个字符占 12 行 6 列
 * *****************************************************************************
 */
void OLED_ShowString(u8 x, u8 y, const char* p)
{
#define MAX_CHAR_POSX 122
#define MAX_CHAR_POSY 58
    while (*p != '\0')
    {
        if (x > MAX_CHAR_POSX)
        {
            x = 0;
            y += 16;
        }
        if (y > MAX_CHAR_POSY)
        {
            y = x = 0;
            OLED_Clear();
        }
        OLED_ShowChar(x, y, *p, 12, 1);
        x += 8;
        p++;
    }
}

/**
 * *****************************************************************************
 * @brief 初始化 OLED
 * *****************************************************************************
 */
void OLED_Init(void)
{
    OLED_RST_Clr();
    HAL_Delay(100);
    OLED_RST_Set();

    OLED_WR_Byte(0xAE, OLED_CMD); //关闭显示
    //设置时钟分频因子,震荡频率
    OLED_WR_Byte(0xD5, OLED_CMD);
    //[3:0],分频因子;[7:4],震荡频率
    OLED_WR_Byte(80, OLED_CMD);
    //设置驱动路数
    OLED_WR_Byte(0xA8, OLED_CMD);
    OLED_WR_Byte(0X3F, OLED_CMD); //默认 0X3F(1/64)
    OLED_WR_Byte(0xD3, OLED_CMD); //设置显示偏移
    OLED_WR_Byte(0X00, OLED_CMD); //默认为 0

    //设置显示开始行 [5:0],行数
    OLED_WR_Byte(0x40, OLED_CMD);

    OLED_WR_Byte(0x8D, OLED_CMD); //电荷泵设置
    OLED_WR_Byte(0x14, OLED_CMD); //bit2，开启/关闭
    OLED_WR_Byte(0x20,
                 OLED_CMD); //设置内存地址模式
    //[1:0],00，列地址模式;01，行地址模式;10,页地址模式;默认10;
    OLED_WR_Byte(0x02, OLED_CMD);
    //段重定义设置,bit0:0,0->0;1,0->127;
    OLED_WR_Byte(0xA1, OLED_CMD);
    //设置COM扫描方向;bit3:0,普通模式;1,重定义模式 COM[N-1]->COM0;N:驱动路数
    OLED_WR_Byte(0xC0, OLED_CMD);
    //设置COM硬件引脚配置
    OLED_WR_Byte(0xDA, OLED_CMD);
    OLED_WR_Byte(0x12, OLED_CMD); //[5:4]配置

    OLED_WR_Byte(0x81, OLED_CMD); //对比度设置
    //1~255;默认 0X7F (亮度设置, 越大越亮)
    OLED_WR_Byte(0xEF, OLED_CMD);
    OLED_WR_Byte(0xD9, OLED_CMD); //设置预充电周期
    OLED_WR_Byte(0xf1, OLED_CMD); //[3:0],PHASE 1;[7:4],PHASE 2;
    OLED_WR_Byte(0xDB, OLED_CMD); //设置 VCOMH 电压倍率
    //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;
    OLED_WR_Byte(0x30, OLED_CMD);
    //全局显示开启;bit0:1,开启;0,关闭;(白屏/黑屏)
    OLED_WR_Byte(0xA4, OLED_CMD);
    //设置显示方式;bit0:1,反相显示;0,正常显示
    OLED_WR_Byte(0xA6, OLED_CMD);
    OLED_WR_Byte(0xAF, OLED_CMD); //开启显示
    OLED_Clear();
}

/**
 * *****************************************************************************
 * @brief 显示汉字
 * @param [in] x 表示显示的水平坐标
 * @param [in] y 表示显示的垂直坐标
 * @param [in] no 表示要显示的汉字 (模组) 在 hzk[][]数组中的行号, 从 0 开始
 * @param [in] font_width 值必须与用字模制作软件生成字模时的点阵值大小一致
 * @param [in] font_height 为用字模制作软件生成字模时字体的高度
 * @note - 这里由于我的屏像素为 32*128--0~7 共 8 页, 每页 4 个位
 * @note - 用这种方法来显示汉字一定要满足用字模生成软件生成的字宽与点阵大小相同才行，否者容易乱码
 * *****************************************************************************
 */
void OLED_ShowCHinese(u8 x, u8 y, u8 no, u8 font_width, u8 font_height)
{
    u8 t, i;
    // font_height 最大值为 32, 这张屏只有 8 个页 (行), 每页 4 个位
    for (i = 0; i < (font_height / 8); i++)
    {
        OLED_Set_Pos(x, y + i);
        //font_width 最大值为 128, 屏幕只有这么大
        for (t = 0; t < font_width; t++)
        {
            OLED_WR_Byte(Hzk16[(font_height / 8) * no + i][t], OLED_DATA);
        }
    }
}

/**
 * *****************************************************************************
 * @brief 设置汉字在屏幕上显示的坐标 (位置)
 * @param [in] x 起点横坐标 
 * @param [in] y 起点纵坐标
 * *****************************************************************************
 */
void OLED_Set_Pos(u8 x, u8 y)
{
    OLED_WR_Byte(0xb0 + y, OLED_CMD);
    OLED_WR_Byte(((x & 0xf0) >> 4) | 0x10, OLED_CMD);
    OLED_WR_Byte((x & 0x0f), OLED_CMD);
}

#ifdef __cplusplus
}
#endif