#ifndef SYS_H
#define SYS_H

#ifdef __cplusplus
extern "C" {
#endif

/* ANCHOR - 头文件包含 */

// #include "main.h"

/* ANCHOR - typedef */

typedef unsigned int   u32; // u32
typedef unsigned char  u8;  // u8
typedef unsigned short u16; // u16

/* ANCHOR - 公共函数声明 */

void floatToString(float num, int precision, char* str);
#ifdef __cplusplus
}
#endif

#endif /* SYS_H */
