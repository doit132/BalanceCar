#ifdef __cplusplus
extern "C" {
#endif

/* ANCHOR - 头文件包含 */

#include "control.h"
#include "key.h"
#include "hcsr04.h"
#include "encoder.h"
#include "motor.h"
#include "control.h"

/* ANCHOR - 全局变量定义 */

/* ANCHOR - 公共函数定义 */

/**
 * *****************************************************************************
 * @brief 限制 PWM 赋值
 * @param [in] IN 输入参数
 * @param [in] max 限幅最大值
 * @param [in] min 限幅最小值
 * @return 限幅后的值
 * *****************************************************************************
 */
int PWM_Limit(int IN, int max, int min)
{
    int OUT = IN;
    if (OUT > max)
        OUT = max;
    if (OUT < min)
        OUT = min;
    return OUT;
}

/**
 * *****************************************************************************
 * @brief 直立 PD 控制
 * @param [in] mpu6050_data MPU6050 数据
 * @return balance: 直立控制 PWM
 * *****************************************************************************
 */
int Control_Balance(MPU6050_Data_t* mpu6050_data)
{
    float Angle_bias, Gyro_bias;
    int   balance;
    Angle_bias = 0 - mpu6050_data->pitch; /* 计算角度偏差值 */
    Gyro_bias = 0 - mpu6050_data->gyro_y; /* 计算角速度偏差值 */
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

/**
 * *****************************************************************************
 * @brief 判断小车是否被拿起
 * @param [in] mpu6050_data MPU6050 数据
 * @param [in] encoder_data 编码器数据
 * @return 拿起返回 1, 未拿起返回 0
 * *****************************************************************************
 */
int Control_Check_Pick_Up(MPU6050_Data_t* mpu6050_data, Encoder_Data_t* encoder_data)
{
    static u16 flag, count0, count1, count2;

    if (flag == 0) /* 条件 1, 小车接近静止 */
    {
        if (abs(Encoder_Data.encoder_count_l) + abs(Encoder_Data.encoder_count_r) < 30)
            count0++;
        else
            count0 = 0;
        if (count0 > 10)
        {
            flag = 1;
            count0 = 0;
        }
    }
    if (flag == 1) /* 条件 2, 小车是在 0 度附近被拿起 */
    {
        if (++count1 > 200)
        {
            count1 = 0;
            flag = 0; /* 超时不再等待 2000ms, 返回第一步 */
        }
        if (mpu6050_data->acc_z > 26000 && (mpu6050_data->pitch > -20) && (mpu6050_data->pitch < 20))
            flag = 2;
    }
    if (flag == 2) /* 条件 3, 小车的轮胎因为正反馈达到最大的转速 */
    {
        if (++count2 > 100)
        {
            count2 = 0;
            flag = 0; /* 超时不再等待 1000ms */
        }
        if (abs(Encoder_Data.encoder_count_l + Encoder_Data.encoder_count_r) > 70)
        {
            flag = 0;
            return 1; /* 检测到小车被拿起 */
        }
    }
    return 0;
}

/**
 * *****************************************************************************
 * @brief MPU6050 数据就绪(Data Ready)中断
 * *****************************************************************************
 */
void MPU6050_DRDY_ISR(uint16_t GPIO_Pin)
{
    extern MPU6050_Data_t MPU6050_Data;
    extern Hcsr04Info_t   Hcsr04Info;
    extern Encoder_Data_t Encoder_Data;
    extern Motor_Data_t   Motor_Data;

    static u8 Flag_Target;                         /* 控制函数相关变量, 提供 10ms 基准 */
    int       Balance_Pwm, Velocity_Pwm, Turn_Pwm; /* 平衡环 PWM, 速度环 PWM, 转向环 PWM */

    if (GPIO_Pin == MPU6050_INT_Pin)
    {
        Flag_Target = !Flag_Target;

        MPU6050_Get_Data(&MPU6050_Data);
        Encoder_Get_Data(&Encoder_Data);
        Motor_Get_Velocity_From_Encoder(&Motor_Data, &Encoder_Data);

        if (Flag_Target == 1) /* 10ms 控制一次 */
        {
            Hcsr04Info.distance = Hcsr04_Read();
            Balance_Pwm = Control_Balance(&MPU6050_Data);
            Motor_Left = Balance_Pwm;
            Motor_Right = Balance_Pwm;
            Motor_Left = PWM_Limit(Motor_Left, 300, -300);
            Motor_Right = PWM_Limit(Motor_Right, 300, -300);
            Motor_Set_Pwm(Motor_Left, Motor_Right);
        }
    }
}

#ifdef __cplusplus
}
#endif
