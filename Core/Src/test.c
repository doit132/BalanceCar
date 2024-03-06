#ifdef __cplusplus
extern "C" {
#endif

/* ANCHOR - 头文件包含 */

#include "test.h"
#include "tim.h"

/* ANCHOR - 公共函数定义 */

void Test_Ultrasonic(void)
{
    u32 distance;
    HAL_TIM_IC_Start(&htim3, TIM_CHANNEL_1);
    while (1)
    {
        distance = Read_Distance();
        printf("distance = %d\r\n", distance);
        HAL_Delay(100);
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
    float pAccelOut[3];
    float pTempOut;
    float pGyroOut[3];
    float pEularAngleOut[3];
    char  buf[20];

    MPU6050_Init();

    while (1)
    {
        MPU6050_Proc();
        MPU6050_GetResult(pAccelOut, &pTempOut, pGyroOut, pEularAngleOut);
        /* 通过串口打印输出结果, 串口重定义无法输出小数, 所以这里先将浮点数转换成字符串 */
        floatToString(pAccelOut[0], 4, buf);
        printf("pAccelOut[0] = %s\r\n", buf);
        floatToString(pAccelOut[1], 4, buf);
        printf("pAccelOut[1] = %s\r\n", buf);
        floatToString(pAccelOut[2], 4, buf);
        printf("pAccelOut[2] = %s\r\n", buf);

        floatToString(pGyroOut[0], 4, buf);
        printf("pGyroOut[0] = %s\r\n", buf);
        floatToString(pGyroOut[1], 4, buf);
        printf("pGyroOut[1] = %s\r\n", buf);
        floatToString(pGyroOut[2], 4, buf);
        printf("pGyroOut[2] = %s\r\n", buf);

        floatToString(pEularAngleOut[0], 4, buf);
        printf("pEularAngleOut[0] = %s\r\n", buf);
        floatToString(pEularAngleOut[1], 4, buf);
        printf("pEularAngleOut[1] = %s\r\n", buf);
        floatToString(pEularAngleOut[2], 4, buf);
        printf("pEularAngleOut[2] = %s\r\n", buf);

        HAL_Delay(100);
    }
}

#ifdef __cplusplus
}
#endif
