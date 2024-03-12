#ifndef HCSR04_H
#define HCSR04_H

#ifdef __cplusplus
extern "C" {
#endif

/* ANCHOR - 头文件包含 */

#include "main.h"

/* ANCHOR - 结构体声明 */

typedef struct
{
    uint8_t               edge_state;           /* 记录上升沿和下降沿状态 */
    uint16_t              tim_overflow_counter; /* 定时器溢出次数 */
    float                 distance;             /* 测量距离 */
    uint32_t              prescaler;
    uint32_t              period;
    uint32_t              t1;            //	上升沿时间
    uint32_t              t2;            //	下降沿时间
    uint32_t              high_level_us; //	高电平持续时间
    TIM_TypeDef*          instance;
    uint32_t              ic_tim_ch;
    HAL_TIM_ActiveChannel active_channel;
} Hcsr04Info_t;

/* ANCHOR - 宏定义 */

/* ANCHOR - 公共函数声明 */
void  HCSR04_Init(TIM_HandleTypeDef* htim, uint32_t Channel);
void  HCSR04_Start(void);
float Hcsr04_Read();

/* 中断处理函数/回调函数 */

void Hcsr04_TIM_Overflow_ISR(TIM_HandleTypeDef* htim);
void Hcsr04_TIM_IC_ISR(TIM_HandleTypeDef* htim);

#ifdef __cplusplus
}
#endif

#endif /* HCSR04_H */
