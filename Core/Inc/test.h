#ifndef TEST_H
#define TEST_H

#ifdef __cplusplus
extern "C" {
#endif

/* ANCHOR - 头文件包含 */

#include "main.h"

/* ANCHOR - 公共函数声明 */

void Test_HCSR04(void);
void Test_Encoder(void);
void Test_Motor(void);
void Test_MPU6050(void);
void Test_OLED(void);
#ifdef __cplusplus
}
#endif

#endif /* TEST_H */
