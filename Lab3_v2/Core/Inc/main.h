/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#define LED_A_SGN_Pin GPIO_PIN_0
#define LED_A_SGN_GPIO_Port GPIOA
#define LED_B_SGN_Pin GPIO_PIN_1
#define LED_B_SGN_GPIO_Port GPIOA
#define LED_C_SGN_Pin GPIO_PIN_2
#define LED_C_SGN_GPIO_Port GPIOA
#define LED_D_SGN_Pin GPIO_PIN_3
#define LED_D_SGN_GPIO_Port GPIOA
#define LED_E_SGN_Pin GPIO_PIN_4
#define LED_E_SGN_GPIO_Port GPIOA
#define LED_F_SGN_Pin GPIO_PIN_5
#define LED_F_SGN_GPIO_Port GPIOA
#define LED_G_SGN_Pin GPIO_PIN_6
#define LED_G_SGN_GPIO_Port GPIOA
#define LED_DOT_SGN_Pin GPIO_PIN_7
#define LED_DOT_SGN_GPIO_Port GPIOA
#define RED_0_SGN_Pin GPIO_PIN_0
#define RED_0_SGN_GPIO_Port GPIOB
#define YEL_0_SGN_Pin GPIO_PIN_1
#define YEL_0_SGN_GPIO_Port GPIOB
#define GRE_0_SGN_Pin GPIO_PIN_2
#define GRE_0_SGN_GPIO_Port GPIOB
#define BTN_0_Pin GPIO_PIN_13
#define BTN_0_GPIO_Port GPIOB
#define BTN_1_Pin GPIO_PIN_14
#define BTN_1_GPIO_Port GPIOB
#define BTN_2_Pin GPIO_PIN_15
#define BTN_2_GPIO_Port GPIOB
#define EN0_SGN_Pin GPIO_PIN_8
#define EN0_SGN_GPIO_Port GPIOA
#define EN1_SGN_Pin GPIO_PIN_9
#define EN1_SGN_GPIO_Port GPIOA
#define EN2_SGN_Pin GPIO_PIN_10
#define EN2_SGN_GPIO_Port GPIOA
#define EN3_SGN_Pin GPIO_PIN_11
#define EN3_SGN_GPIO_Port GPIOA
#define LED_RED_SGN_Pin GPIO_PIN_12
#define LED_RED_SGN_GPIO_Port GPIOA
#define RED_1_SGN_Pin GPIO_PIN_3
#define RED_1_SGN_GPIO_Port GPIOB
#define YEL_1_SGN_Pin GPIO_PIN_4
#define YEL_1_SGN_GPIO_Port GPIOB
#define GRE_1_SGN_Pin GPIO_PIN_5
#define GRE_1_SGN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
