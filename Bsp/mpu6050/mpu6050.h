#ifndef MPU6050_H
#define MPU6050_H

#ifdef __cplusplus
extern "C" {
#endif

/* ANCHOR - 头文件包含 */

#include "main.h"

/* ANCHOR - 结构体声明 */

/* 定义一个结构体, 存放 MPU6050 传感器数据 */
typedef struct
{
    float acc_x; /* 加速度计 x 轴加速度 */
    float acc_y; /* 加速度计 y 轴加速度 */
    float acc_z; /* 加速度计 z 轴加速度 */

    float gyro_x; /* 陀螺仪 x 轴角速度 */
    float gyro_y; /* 陀螺仪 y 轴角速度 */
    float gyro_z; /* 陀螺仪 z 轴角速度 */

    float temp; /* 温度 */

    float pitch; /* 俯仰角 */
    float roll;  /* 翻滚角 */
    float yaw;   /* 偏航角 */
} MPU6050_Data_t;

/* ANCHOR - 函数声明 */
u8   MPU6050_Get_DeviceID(void);
u8   MPU6050_Check_Connect(void);
void MPU6050_Init(MPU6050_Data_t* pData);
void MPU6050_Get_Data(MPU6050_Data_t* pData);
#ifdef __cplusplus
}
#endif

#endif /* MPU6050_H */
