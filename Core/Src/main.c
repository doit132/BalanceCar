/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "test.h"

/* 板级支持包相关 */
#include "led.h"
#include "oled.h"
#include "mpu6050.h"
#include "hcsr04.h"
#include "encoder.h"
#include "motor.h"
#include "key.h"
#include "show.h"

/* 辅助文件 */
#include "delay.h"
#include "soft_timer.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
Encoder_Data_t Encoder_Data;
Motor_Data_t   Motor_Data;
MPU6050_Data_t MPU6050_Data;
Hcsr04Info_t   Hcsr04Info;

u8          Way_Angle = 2; /* 获取角度的算法, 1: 四元数  2: 卡尔曼  3: 互补滤波 */
u8          Flag_front, Flag_back, Flag_Left, Flag_Right, Flag_velocity = 2; /* 蓝牙遥控相关的变量 */
u8          Flag_Stop = 1, Flag_Show = 0; /* 电机停止标志位和显示标志位  默认停止 显示打开 */
int         Voltage;                      /* 电池电压采样相关的变量 */
float       Angle_Balance, Gyro_Balance, Gyro_Turn; /* 平衡倾角 平衡陀螺仪 转向陀螺仪 */
u8          PID_Send;                               /* 调参相关变量 */
u8          Flag_follow = 0, Flag_avoid = 0;        /* 超声波跟随、超声波壁障标志位 */
volatile u8 delay_flag, delay_50;                   /* 提供延时的变量 */
float       Balance_Kp = 22500, Balance_Kd = 108;   /* 定义平衡环 PID 参数 */
float       Velocity_Kp = 16000, Velocity_Ki = 80;  /* 定义速度环 PID 参数 */
float       Turn_Kp = 4200, Turn_Kd = 0;            /* 定义转向环 PID 参数 PID 参数 (放大 100 倍) */
int         Motor_Left, Motor_Right;                /* 存放电机经过 PID 控制之后的 PWM */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static void BSP_Init(void)
{
    OLED_Init();
    Encoder_Init(&Encoder_Data);
    Motor_Init(&Motor_Data);
    MPU6050_Init(&MPU6050_Data);
    HCSR04_Init(&htim3, TIM_CHANNEL_3);
    OLED_Init();
    SoftTimer_Init();
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_I2C1_Init();
    MX_TIM3_Init();
    MX_TIM2_Init();
    MX_TIM1_Init();
    MX_TIM4_Init();
    MX_ADC1_Init();
    /* USER CODE BEGIN 2 */
    BSP_Init();
    /* 原本由 CubeMX 工具生成的代码是 HAL_NVIC_EnableIRQ(EXTI15_10_IRQn) 由于生成的代码总在用户代码之上
    这个中断是需要所有的外设初始化完毕最后才能开启的, 所以在 MX_GPIO_Init 中先失能, 在所有外设初始化完成后再使能 */
    // HAL_NVIC_EnableIRQ(EXTI15_10_IRQn); /* 开启引脚外部中断 */

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */

    while (1)
    {
        // Test_HCSR04();
        // Test_Encoder();
        // Test_Motor();
        // Test_MPU6050();
        // Test_OLED();
        // Test_Main();
        // Test_ADC();
        // Test_SoftTimer();

        if (Flag_Show == 0) /* 使用 OLED 显示屏 */
        {
            OLED_Show();
        }
        delay_flag = 1;
        delay_50 = 0;
        while (delay_flag)
            ; /* 示波器需要 50ms 高精度延时, delay 函数不满足要求, 故使用 MPU6050 中断提供 50ms 延时 */

        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef       RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef       RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
  */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
    PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
