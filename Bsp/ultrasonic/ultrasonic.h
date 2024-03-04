#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#ifdef __cplusplus
extern "C" {
#endif

/* ANCHOR - 头文件包含 */

#include "main.h"

/* ANCHOR - 宏定义 */

#define Trigger_RESET()                                                        \
    HAL_GPIO_WritePin(Trigger_GPIO_Port, Trigger_Pin, GPIO_PIN_RESET)
#define Trigger_SET()                                                          \
    HAL_GPIO_WritePin(Trigger_GPIO_Port, Trigger_Pin, GPIO_PIN_SET)

/* ANCHOR - 全局变量声明 */

extern u16 TIM3CH3_CAPTURE_STA, TIM3CH3_CAPTURE_VAL;

/* ANCHOR - 公共函数声明 */

u32 Read_Distance(void);

#ifdef __cplusplus
}
#endif

#endif /* ULTRASONIC_H */
