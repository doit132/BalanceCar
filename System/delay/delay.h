#ifndef DELAY_H
#define DELAY_H

#ifdef __cplusplus
extern "C" {
#endif

/* ANCHOR - 头文件包含 */
#include "sys.h"

/* ANCHOR - 函数声明 */
void delay_init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#ifdef __cplusplus
}
#endif

#endif /* DELAY_H */
