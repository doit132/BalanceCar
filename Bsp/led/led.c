#ifdef __cplusplus
extern "C" {
#endif

#include "led.h"

/**
 * *****************************************************************************
 * @brief LED 闪烁
 * @param[in] time 闪烁时间 (ms) 
 * *****************************************************************************
 */
void LED_Flash(u32 time)
{
    LED_Toggle();
    HAL_Delay(time);
}

#ifdef __cplusplus
}
#endif
