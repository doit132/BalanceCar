#ifdef __cplusplus
extern "C" {
#endif

/* ANCHOR - 头文件包含 */

#include "sys_usart.h"
#include "usart.h"

/* ANCHOR - gcc printf 重定义 */

#if 1 /* printf 重定义 */
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE* f)
#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE
{
    // /* 实现串口发送一个字节数据的函数 */
    // while ((USART1->SR & 0x40) == 0)
    // {
    // }
    // USART1->DR = (uint8_t)ch;
    // return ch;
    HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, 0xFFFF);

    return ch;
}

int _write(int file, char* ptr, int len)
{
    int DataIdx;
    for (DataIdx = 0; DataIdx < len; DataIdx++)
    {
        __io_putchar(*ptr++);
    }
    return len;
}
#endif /* printf 重定义 */

#ifdef __cplusplus
}
#endif
