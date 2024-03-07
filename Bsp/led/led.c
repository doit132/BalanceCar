#ifdef __cplusplus
extern "C" {
#endif

/* ANCHOR - 头文件包含 */

#include "led.h"

/* ANCHOR - 公共函数定义 */

/**
 * *****************************************************************************
 * @brief LED 闪烁
 * @param [in] time 闪烁时间 (ms) 
 * *****************************************************************************
 */
void LED_Flash(u32 time)
{
    LED_Toggle();
    // HAL_Delay(time);
    delay_ms(time);
}

#ifdef __cplusplus
}
#endif
