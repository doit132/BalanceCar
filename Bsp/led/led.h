#ifndef LED_H
#define LED_H

#ifdef __cplusplus
extern "C" {
#endif

/* ANCHOR - 头文件包含 */

#include "sys.h"
#include "main.h"

/* ANCHOR - 宏定义 */

#define LED_ON()     HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET)
#define LED_OFF()    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET)
#define LED_Toggle() HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin)

/* ANCHOR - 公共函数声明 */

void LED_Flash(u32 time);

#ifdef __cplusplus
}
#endif

#endif /* LED_H */
