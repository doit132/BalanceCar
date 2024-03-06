#ifdef __cplusplus
extern "C" {
#endif

/* ANCHOR - 头文件包含 */

#include "motor.h"
#include "tim.h"

/* ANCHOR - 宏定义 */

/* 表示电机的编号 */
#define LEFT_MOTOR  1
#define RIGHT_MOTOR 2
#define ALL_MOTOR   3

/* 表示电机的转动方向 */
#define FORWARD  1
#define BACKWARD 2

/* ANCHOR - 公共函数定义 */

/**
 * *****************************************************************************
 * @brief 通过编码器来计算车轮行驶速度
 * @param [in] encoder_left 左轮编码器数值
 * @param [in] encoder_right 右轮编码器数值
 * @param [out] wheel_speed 存放车轮速度的数组
 * @note - wheel_speed[0] 表示左轮速度
 * @note - wheel_speed[1] 表示右轮速度
 * *****************************************************************************
 */
void Get_Velocity_Form_Encoder(int   encoder_left,
                               int   encoder_right,
                               float wheel_speed[])
{
    float rotation_speed_l, rotation_speed_r;
    /**
     * 1. 计算角速度 (轮子旋转速度)
     * 2. 计算线速度 (车轮行进速度)
     */
    rotation_speed_l = encoder_left * CONTROL_FREQUENCY / ENCODER_MULTIPLES /
                       REDUCTION_RATIO / ENCODER_PRECISION;
    wheel_speed[0] = rotation_speed_l * PI * DIAMETER_67;
    rotation_speed_r = encoder_right * CONTROL_FREQUENCY / ENCODER_MULTIPLES /
                       REDUCTION_RATIO / ENCODER_PRECISION;
    wheel_speed[1] = rotation_speed_r * PI * DIAMETER_67;
}

/**
 * *****************************************************************************
 * @brief 设置电机转向
 * @param [in] motor 控制哪一个电机
 * @param [in] direction 方向
 * @note - direction = 1 表示正转 (顺时针, 前进), direction = 0 表示反转 (逆时针, 后退)
 * @note - motor = 1 表示左电机, motor = 2 表示右电机
 * *****************************************************************************
 */
static void Motor_Set_Direction(u8 motor, u8 direction)
{
    if (motor == 1)
    {
        if (direction == 1)
        {
            HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET);
            return;
        }
        HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET);
        return;
    }

    if (direction == 1)
    {
        HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_SET);
        return;
    }
    HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET);
}

/**
 * *****************************************************************************
 * @brief 停止电机转动
 * @param [in] motor 要停止的电机
 * @note - motor = 1 表示左电机, motor = 2 表示右电机, motor = 3 表示全部
 * *****************************************************************************
 */
void Motor_TurnOff(u8 motor)
{
    if (motor == 1 || motor == 3)
    {
        HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET);
    }
    if (motor == 2 || motor == 3)
    {
        HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_SET);
    }
}

/**
 * *****************************************************************************
 * @brief 给电机设置 PWM 占空比, 如果是负值后退, 如果是正值, 前进
 * @param [in] motor_left 
 * @param [in] motor_right 
 * *****************************************************************************
 */
void Motor_Set_Pwm(int motor_left, int motor_right)
{
    if (motor_left > 0)
        Motor_Set_Direction(LEFT_MOTOR, FORWARD);
    else
        Motor_Set_Direction(LEFT_MOTOR, BACKWARD);
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, motor_left);

    if (motor_right > 0)
        Motor_Set_Direction(RIGHT_MOTOR, FORWARD);
    else
        Motor_Set_Direction(RIGHT_MOTOR, BACKWARD);
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_4, motor_right);
}
#ifdef __cplusplus
}
#endif
