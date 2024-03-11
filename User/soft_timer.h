#ifndef SOFT_TIMER_H
#define SOFT_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

/* ANCHOR - 头文件包含 */

#include "main.h"

/* ANCHOR - 宏定义 */

/* 配置项 */
#define TMR_COUNT       4  /* 软件定时器的个数 (定时器 ID 范围 0 - 3) */
#define TMR_NAME_LENGTH 20 /* 软件定时器名长度 */

/* ANCHOR - 枚举定义 */

typedef enum soft_timer_mode
{
    SOFT_TIMER_MODE_ONCE = 0,
    SOFT_TIMER_MODE_PERIODIC,
    SOFT_TIMER_MODE_MAX
} soft_timer_mode_t;

/* ANCHOR - 结构体声明 */

/* 定时器结构体, 成员变量必须是 volatile, 否则 C 编译器优化时可能有问题 */
typedef struct
{
    volatile uint8_t  Mode;                  /* 计数器模式, 1 次性 */
    volatile uint8_t  Flag;                  /* 定时到达标志  */
    volatile uint32_t Count;                 /* 计数器 */
    volatile uint32_t PreLoad;               /* 计数器预装值 */
    char              Name[TMR_NAME_LENGTH]; /* 软件定时器名 */
} soft_timer_t;

/* ANCHOR - 公共函数声明 */

void SysTick_ISR(void);

void    SoftTimer_Init(void);
uint8_t SoftTimer_Check(uint8_t _id);
void    SoftTimer_Start(uint8_t _id, uint32_t _period, soft_timer_mode_t _mode, const char* name);
#ifdef __cplusplus
}
#endif

#endif /* SOFT_TIMER_H */
