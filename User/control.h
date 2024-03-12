#ifndef CONTROL_H
#define CONTROL_H

#ifdef __cplusplus
extern "C" {
#endif

/* ANCHOR - 头文件包含 */

#include "sys.h"

/* ANCHOR - 宏定义 */

#define INT HAL_GPIO_ReadPin(MPU6050_INT_GPIO_Port, MPU6050_INT_Pin) /* PA12 连接到 MPU6050 的中断引脚 */

/* ANCHOR - 结构体声明 */

/* ANCHOR - 公共函数声明 */

int Control_Balance(MPU6050_Data_t* mpu6050_data);

/* 中断回调函数 */

void MPU6050_DRDY_ISR(uint16_t GPIO_Pin);
#ifdef __cplusplus
}
#endif

#endif /* CONTROL_H */
