#ifdef __cplusplus
extern "C" {
#endif

/* ANCHOR - 头文件包含 */

#include "control.h"
#include "key.h"

/* ANCHOR - 全局变量定义 */

float Balance_Kp = 22500, Balance_Kd = 108;  // 定义平衡环PID参数
float Velocity_Kp = 16000, Velocity_Ki = 80; // 定义速度环PID参数
float Turn_Kp = 4200, Turn_Kd = 0;           // 定义转向环PID参数
/* ANCHOR - 公共函数定义 */

/**
 * *****************************************************************************
 * @brief 直立 PD 控制
 * @param [in] Angle 当前小车俯仰角度
 * @param [in] Gyro 角速度
 * @return balance: 直立控制 PWM
 * *****************************************************************************
 */
int Control_Balance(float Angle, float Gyro)
{
    float Angle_bias, Gyro_bias;
    int   balance;
    Angle_bias = 0 - Angle; /* 计算角度偏差值 */
    Gyro_bias = 0 - Gyro;   /* 计算角速度偏差值 */
    /* 计算平衡控制的电机 PWM  PD 控制   kp 是 P 系数 kd 是 D 系数 */
    balance = -Balance_Kp / 100 * Angle_bias - Gyro_bias * Balance_Kd / 100;
    return balance;
}

/**
 * *****************************************************************************
 * @brief 速度控制 PWM	
 * @param [in] encoder_left 左轮编码器读数
 * @param [in] encoder_right 右轮编码器读数
 * @return 速度控制 PWM
 * @note - 修改前进后退速度, 请修改 Target_Velocity, 比如, 改成 60 就比较慢了
 * *****************************************************************************
 */
int Control_Velocity(int encoder_left, int encoder_right)
{
    /* 计算速度控制的电机 PWM */
    return 0;
}

#ifdef __cplusplus
}
#endif
