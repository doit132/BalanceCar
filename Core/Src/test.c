#ifdef __cplusplus
extern "C" {
#endif

/* ANCHOR - 头文件包含 */

#include "test.h"
#include "tim.h"
#include "hcsr04.h"
#include "mpu6050.h"
#include "encoder.h"
#include "motor.h"
#include "oled.h"
#include "soft_timer.h"
#include "show.h"
#include "adc.h"

/* ANCHOR - 全局变量定义 */

/* ANCHOR - 公共函数定义 */

void Test_HCSR04(void)
{
    float dist;
    HCSR04_Init(&htim3, TIM_CHANNEL_3);
    HCSR04_Start();
    while (1)
    {
        dist = Hcsr04_Read();
        HCSR04_Start();
        printf("dist = %.2f \r\n", dist);
        // HAL_Delay(200);
    }
}

void Test_OLED(void)
{
    OLED_Init();
    while (1)
    {
        OLED_ShowString(0, 0, "Hello, World!");
        OLED_Refresh_Gram();
    }
}

void Test_Encoder_Get_Data(void)
{
    Encoder_Data_t Encoder_Data;
    Encoder_Init(&Encoder_Data);
    while (1)
    {
        Encoder_Get_Data(&Encoder_Data);
        printf("encoder_count_l = %d\r\n", Encoder_Data.encoder_count_l);
        printf("encoder_count_r = %d\r\n", Encoder_Data.encoder_count_r);
        HAL_Delay(3000);
    }
}

void Test_Encoder(void)
{
    Test_Encoder_Get_Data();
}

void Test_Motor_Direction(void)
{
    Motor_Data_t Motor_Data;
    Motor_Init(&Motor_Data);

    // Motor_Set_Pwm(0, 100);
    // Motor_Set_Pwm(100, 0);
    Motor_Set_Pwm(100, 100);
    HAL_Delay(2000);
    Motor_TurnOff(3);
    while (1)
    {
    }
}

void Test_Motor_Velocity(void)
{
    /* 定义变量存放数据 */
    Encoder_Data_t Encoder_Data;
    Motor_Data_t   Motor_Data;

    /* 初始化 */
    Motor_Init(&Motor_Data);
    Encoder_Init(&Encoder_Data);

    /* 测试 */
    Motor_Set_Pwm(100, 100);
    while (1)
    {
        Encoder_Get_Data(&Encoder_Data);
        Motor_Get_Velocity_From_Encoder(&Motor_Data, &Encoder_Data);
        printf("velocity = %f mm/s\r\n", Motor_Data.Velocity_Left);
        printf("velocity = %f mm/s\r\n", Motor_Data.Velocity_Right);
        HAL_Delay(1000);
    }
}

void Test_Motor(void)
{
    // Test_Motor_Direction();
    // Test_Motor_Velocity();
}

void Test_MPU6050(void)
{
    /* 定义变量存放数据 */
    MPU6050_Data_t MPU6050_Data;

    /* 初始化 MPU6050 */
    MPU6050_Init(&MPU6050_Data);

    while (1)
    {
        MPU6050_Get_Data(&MPU6050_Data);

        // printf("\r\n");
        // /* 通过串口打印输出结果, 串口重定义无法输出小数, 所以这里先将浮点数转换成字符串 */
        // printf("acc_x = %.2f\r\n", MPU6050_Data.acc_x);
        // printf("acc_y = %.2f\r\n", MPU6050_Data.acc_y);
        // printf("acc_z = %.2f\r\n", MPU6050_Data.acc_z);
        // printf("temp = %.2f\r\n", MPU6050_Data.temp);
        // printf("gyro_x = %.2f\r\n", MPU6050_Data.gyro_x);
        // printf("gyro_y = %.2f\r\n", MPU6050_Data.gyro_y);
        // printf("gyro_z = %.2f\r\n", MPU6050_Data.gyro_z);
        // printf("yaw = %.2f\r\n", MPU6050_Data.yaw);
        // printf("roll = %.2f\r\n", MPU6050_Data.roll);
        // printf("pitch = %.2f\r\n", MPU6050_Data.pitch);
        // printf("--------------------------");
        printf("$%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f;\r\n",
               MPU6050_Data.acc_x,
               MPU6050_Data.acc_y,
               MPU6050_Data.acc_z,
               MPU6050_Data.gyro_x,
               MPU6050_Data.gyro_y,
               MPU6050_Data.gyro_z,
               MPU6050_Data.yaw,
               MPU6050_Data.roll,
               MPU6050_Data.pitch,
               MPU6050_Data.temp);
    }
}

void Test_Main(void)
{
    /* 定义变量存放数据 */
    extern Encoder_Data_t Encoder_Data;
    extern Motor_Data_t   Motor_Data;
    extern MPU6050_Data_t MPU6050_Data;

    /* 测试 */
    // Motor_Set_Pwm(500, 500);

    SoftTimer_Start(0, 5, SOFT_TIMER_MODE_PERIODIC, "Encoder");
    SoftTimer_Start(1, 300, SOFT_TIMER_MODE_PERIODIC, "OLED");
    SoftTimer_Start(2, 300, SOFT_TIMER_MODE_PERIODIC, "HCSR04");

    while (1)
    {
        // if (SoftTimer_Check(0))
        // {
        //     Encoder_Get_Data(&Encoder_Data);
        //     Encoder_Change_Mode(&Encoder_Data);

        //     Motor_Get_Velocity_From_Encoder(&Motor_Data, &Encoder_Data);
        //     printf("--------------------------\r\n");
        //     printf("encoder_count_l = %d\r\n", Encoder_Data.encoder_count_l);
        //     printf("encoder_count_r = %d\r\n", Encoder_Data.encoder_count_r);
        //     printf("velocity_l = %.2f mm/s\r\n", Motor_Data.Velocity_Left);
        //     printf("velocity_r = %.2f mm/s\r\n", Motor_Data.Velocity_Right);
        //     printf("yaw: %.2f \r\n", MPU6050_Data.yaw);
        //     printf("roll: %.2f \r\n", MPU6050_Data.roll);
        //     printf("pitch: %.2f \r\n", MPU6050_Data.pitch);
        //     printf("--------------------------\r\n");
        // }
        if (SoftTimer_Check(1))
        {
            OLED_Show();
        }
        // if (SoftTimer_Check(2))
        // {
        //     HCSR04_Start();
        //     Hcsr04Info.distance = Hcsr04_Read();
        // }
    }
}

void Test_ADC(void)
{
    int voltage;
    while (1)
    {
        voltage = ADC_Get_Battery_Volt();
        printf("voltage = %d mv\r\n", voltage);
    }
}

void Test_SoftTimer(void)
{
    /* 定义变量存放数据 */
    Encoder_Data_t Encoder_Data;

    SoftTimer_Init();
    Encoder_Init(&Encoder_Data);

    // SoftTimer_Start(1, 1000, SOFT_TIMER_MODE_ONCE);
    SoftTimer_Start(1, 1000, SOFT_TIMER_MODE_ONCE, "串口");
    SoftTimer_Start(2, 1000, SOFT_TIMER_MODE_PERIODIC, "Encoder");
    while (1)
    {
        if (SoftTimer_Check(1))
        {
            // printf("timer 1 done\r\n");
        }
        if (SoftTimer_Check(2))
        {
            Encoder_Get_Data(&Encoder_Data);
            printf("--------------------------\r\n");
            printf("encoder_count_l = %d\r\n", Encoder_Data.encoder_count_l);
            printf("encoder_count_r = %d\r\n", Encoder_Data.encoder_count_r);
            printf("--------------------------\r\n");
        }
    }
}

#ifdef __cplusplus
}
#endif
