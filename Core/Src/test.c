#ifdef __cplusplus
extern "C" {
#endif

/* ANCHOR - 头文件包含 */

#include "test.h"
#include "tim.h"

/* ANCHOR - 全局变量定义 */

/* ANCHOR - 公共函数定义 */

void Test_HCSR04(void)
{
    float dist;
    char  buf[20];
    HCSR04_Init(&htim3, TIM_CHANNEL_3);
    HCSR04_Start();
    while (1)
    {
        dist = Hcsr04_Read();
        HCSR04_Start();
        floatToString(dist, 2, buf);
        printf("dist =%s cm\r\n", buf);
        HAL_Delay(200);
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

void Test_Encoder(void)
{
    int encoder_num_l = 0, encoder_num_r = 0;
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1 | TIM_CHANNEL_2);
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_1 | TIM_CHANNEL_2);
    while (1)
    {
        encoder_num_l = Read_Encoder(2);
        encoder_num_r = Read_Encoder(4);
        printf("encoder_num_l = %d\r\n", encoder_num_l);
        printf("encoder_num_r = %d\r\n", encoder_num_r);
        HAL_Delay(3000);
    }
}

void Test_Motor(void)
{
    HAL_TIM_PWM_Init(&htim1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
    Motor_Set_Pwm(1000, 0);
    HAL_Delay(2000);
    Motor_TurnOff(3);
    while (1)
    {
    }
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

#ifdef __cplusplus
}
#endif
