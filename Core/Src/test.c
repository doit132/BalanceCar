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
    u32 encoder_num = 0;
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1 | TIM_CHANNEL_2);
    while (1)
    {
        encoder_num = Read_Encoder(2);
        printf("encoder_num = %du\r\n", encoder_num);
        HAL_Delay(100);
    }
}

#ifdef __cplusplus
}
#endif
