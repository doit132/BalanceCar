#ifdef __cplusplus
extern "C" {
#endif

/* ANCHOR - 头文件包含 */

#include "encoder.h"
#include "tim.h"

/* ANCHOR - 公共函数定义 */

/**
 * *****************************************************************************
 * @brief 读取编码器的计数器数值
 * @param [in] TIMX 读哪个定时器 
 * @note - TIMX 的取值
 * @note    - 2: TIM2
 * @note    - 3: TIM3
 * @note    - 4: TIM4
 * @return 将编码器计数器的数值返回
 * *****************************************************************************
 */
int Read_Encoder(u8 TIMX)
{
    int Encoder_TIM;
    switch (TIMX)
    {
        case 2:
            Encoder_TIM = (short)__HAL_TIM_GetCounter(&htim2);
            __HAL_TIM_SetCounter(&htim2, 0);
            break;
        case 3:
            Encoder_TIM = (short)__HAL_TIM_GetCounter(&htim3);
            __HAL_TIM_SetCounter(&htim3, 0);
            break;
        case 4:
            Encoder_TIM = (short)__HAL_TIM_GetCounter(&htim4);
            __HAL_TIM_SetCounter(&htim4, 0);
            break;
        default:
            Encoder_TIM = 0;
    }
    return Encoder_TIM;
}

#ifdef __cplusplus
}
#endif
