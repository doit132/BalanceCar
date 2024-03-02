#ifdef __cplusplus
extern "C" {
#endif

/* ANCHOR - 头文件包含 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "sys.h"

/* ANCHOR - 私有函数定义 */

/**
 * *****************************************************************************
 * @brief 翻转字符串
 * @param [in] str 要翻转的字符串
 * @param [in] length 要翻转的长度
 * @note - Str_Reverse("Hello", 3); -> leHlo
 * *****************************************************************************
 */
static void Str_Reverse(char* str, int length)
{
    int  start = 0;
    int  end = length - 1;
    char temp;

    while (start < end)
    {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

/* ANCHOR - 公共函数定义 */

/**
 * *****************************************************************************
 * @brief 将浮点数转换为字符串, 可设置精度
 * @param [in] num 要转换的浮点数
 * @param [in] precision 保留的小数位数
 * @param [out] str 存储转换后的结果
 * *****************************************************************************
 */
void floatToString(float num, int precision, char* str)
{
    // 处理负数
    if (num < 0)
    {
        str[0] = '-';
        num = -num;
        str++;
    }

    int   integerPart = (int)num;
    float fractionalPart = num - (float)integerPart;

    // 处理整数部分
    int i = 0;
    if (integerPart == 0)
    {
        str[i++] = '0';
    }
    else
    {
        while (integerPart != 0)
        {
            str[i++] = (integerPart % 10) + '0';
            integerPart /= 10;
        }
        Str_Reverse(str, i);
    }

    // 添加小数点
    str[i++] = '.';

    // 处理小数部分
    int j = 0;
    while (precision > 0)
    {
        fractionalPart *= 10;
        int digit = (int)fractionalPart;
        str[i + j] = digit + '0';
        fractionalPart -= digit;
        precision--;
        j++;
    }

    str[i + j] = '\0'; // 添加字符串结束符
}

#ifdef __cplusplus
}
#endif
