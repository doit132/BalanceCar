/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

typedef unsigned int   u32; // u32
typedef unsigned char  u8;  // u8
typedef unsigned short u16; // u16

/* ANCHOR - 头文件包含 */

/* C 语言库相关头文件 */
#include "stdio.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Encoder_Left_A_Pin       GPIO_PIN_0
#define Encoder_Left_A_GPIO_Port GPIOA
#define Encoder_Left_B_Pin       GPIO_PIN_1
#define Encoder_Left_B_GPIO_Port GPIOA
#define LED_Pin                  GPIO_PIN_4
#define LED_GPIO_Port            GPIOA
#define User_key_Pin             GPIO_PIN_5
#define User_key_GPIO_Port       GPIOA
#define ADC_Voltage_Pin          GPIO_PIN_6
#define ADC_Voltage_GPIO_Port    GPIOA
#define HCSR04_ECHO_Pin          GPIO_PIN_0
#define HCSR04_ECHO_GPIO_Port    GPIOB
#define TRIG_Pin                 GPIO_PIN_1
#define TRIG_GPIO_Port           GPIOB
#define BIN2_Pin                 GPIO_PIN_12
#define BIN2_GPIO_Port           GPIOB
#define BIN1_Pin                 GPIO_PIN_13
#define BIN1_GPIO_Port           GPIOB
#define AIN1_Pin                 GPIO_PIN_14
#define AIN1_GPIO_Port           GPIOB
#define AIN2_Pin                 GPIO_PIN_15
#define AIN2_GPIO_Port           GPIOB
#define PWM_Right_Pin            GPIO_PIN_8
#define PWM_Right_GPIO_Port      GPIOA
#define PWM_Left_Pin             GPIO_PIN_11
#define PWM_Left_GPIO_Port       GPIOA
#define MPU6050_INT_Pin          GPIO_PIN_12
#define MPU6050_INT_GPIO_Port    GPIOA
#define MPU6050_INT_EXTI_IRQn    EXTI15_10_IRQn
#define OLED_DC_Pin              GPIO_PIN_15
#define OLED_DC_GPIO_Port        GPIOA
#define OLED_RES_Pin             GPIO_PIN_3
#define OLED_RES_GPIO_Port       GPIOB
#define OLED_SDA_Pin             GPIO_PIN_4
#define OLED_SDA_GPIO_Port       GPIOB
#define OLED_SCL_Pin             GPIO_PIN_5
#define OLED_SCL_GPIO_Port       GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
