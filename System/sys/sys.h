#ifndef SYS_H
#define SYS_H

#ifdef __cplusplus
extern "C" {
#endif

/* ANCHOR - 头文件包含 */

#include "main.h"

/* ANCHOR - 公共函数声明 */

void floatToString(float num, int precision, char* str);
#ifdef __cplusplus
}
#endif

#endif /* SYS_H */
