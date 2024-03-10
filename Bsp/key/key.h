#ifndef KEY_H
#define KEY_H

#ifdef __cplusplus
extern "C" {
#endif

/* ANCHOR - 头文件包含 */

#include "sys.h"
#include "main.h"

/* ANCHOR - 宏定义 */

#define KEY HAL_GPIO_ReadPin(User_key_GPIO_Port, User_key_Pin)

/* ANCHOR - 公共函数声明 */

/**
 * *****************************************************************************
 * @brief 检测按键是否单击
 * @return 按键状态  0: 无动作 1: 单击 
 * *****************************************************************************
 */
u8 Check_Key_Click(void);
#ifdef __cplusplus
}
#endif

#endif /* KEY_H */
