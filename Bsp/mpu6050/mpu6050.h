#ifndef MPU6050_H
#define MPU6050_H

#ifdef __cplusplus
extern "C" {
#endif

/* ANCHOR - 头文件包含 */

#include "main.h"

/* ANCHOR - 函数声明 */
u8   MPU6050_Get_DeviceID(void);
u8   MPU6050_Check_Connect(void);
void MPU6050_Init(void);
void MPU6050_Proc(void);
void MPU6050_GetResult(float* pAccelOut,
                       float* pTempOut,
                       float* pGyroOut,
                       float* pEularAngleOut);
#ifdef __cplusplus
}
#endif

#endif /* MPU6050_H */
