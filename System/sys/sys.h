#ifndef SYS_H
#define SYS_H

#ifdef __cplusplus
extern "C" {
#endif

/* ANCHOR - 头文件包含 */

#include "main.h"
#include "encoder.h"
#include "motor.h"
#include "hcsr04.h"
#include "mpu6050.h"

/* ANCHOR - 全局变量 */

extern u8          Way_Angle; /* 获取角度的算法, 1: 四元数  2: 卡尔曼  3: 互补滤波 */
extern u8          Flag_front, Flag_back, Flag_Left, Flag_Right, Flag_velocity; /* 蓝牙遥控相关的变量 */
extern u8          Flag_Stop, Flag_Show; /* 电机停止标志位和显示标志位  默认停止 显示打开 */
extern int         Voltage;              /* 电池电压采样相关的变量 */
extern float       Angle_Balance, Gyro_Balance, Gyro_Turn; /* 平衡倾角 平衡陀螺仪 转向陀螺仪 */
extern u8          PID_Send;                               /* 调参相关变量 */
extern u8          Flag_follow, Flag_avoid;                /* 超声波跟随、超声波壁障标志位 */
extern volatile u8 delay_flag, delay_50;                   /* 提供延时的变量 */
extern float       Balance_Kp, Balance_Kd;
extern float       Velocity_Kp, Velocity_Ki;
extern float       Turn_Kp, Turn_Kd;        /* PID 参数(放大 100 倍) */
extern int         Motor_Left, Motor_Right; /* 存放电机经过 PID 控制之后的 PWM */

extern Encoder_Data_t Encoder_Data;
extern Motor_Data_t   Motor_Data;
extern MPU6050_Data_t MPU6050_Data;
extern Hcsr04Info_t   Hcsr04Info;

/* ANCHOR - typedef */

/* ANCHOR - 公共函数声明 */

void floatToString(float num, int precision, char* str);
#ifdef __cplusplus
}
#endif

#endif /* SYS_H */
