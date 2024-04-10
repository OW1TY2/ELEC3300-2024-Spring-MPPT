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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LCD_RST_Pin GPIO_PIN_2
#define LCD_RST_GPIO_Port GPIOE
#define CPT_RST_Pin GPIO_PIN_3
#define CPT_RST_GPIO_Port GPIOE
#define CPT_INT_Pin GPIO_PIN_4
#define CPT_INT_GPIO_Port GPIOE
#define INPUT_CURRENT_ADC_Pin GPIO_PIN_0
#define INPUT_CURRENT_ADC_GPIO_Port GPIOC
#define INPUT_VOLTAGE_ADC_Pin GPIO_PIN_1
#define INPUT_VOLTAGE_ADC_GPIO_Port GPIOC
#define OUTPUT_VOLTAGE_ADC_Pin GPIO_PIN_2
#define OUTPUT_VOLTAGE_ADC_GPIO_Port GPIOC
#define OUTPUT_CURRENT_ADC_Pin GPIO_PIN_3
#define OUTPUT_CURRENT_ADC_GPIO_Port GPIOC
#define LCD_PWM_Pin GPIO_PIN_1
#define LCD_PWM_GPIO_Port GPIOA
#define SPI1_CS_Pin GPIO_PIN_4
#define SPI1_CS_GPIO_Port GPIOA
#define LDR1_ADC_Pin GPIO_PIN_5
#define LDR1_ADC_GPIO_Port GPIOA
#define PWM_PITCH_1_Pin GPIO_PIN_6
#define PWM_PITCH_1_GPIO_Port GPIOA
#define PWM_PITCH_2_Pin GPIO_PIN_7
#define PWM_PITCH_2_GPIO_Port GPIOA
#define LDR2_ADC_Pin GPIO_PIN_4
#define LDR2_ADC_GPIO_Port GPIOC
#define LDR3_ADC_Pin GPIO_PIN_5
#define LDR3_ADC_GPIO_Port GPIOC
#define LDR4_ADC_Pin GPIO_PIN_0
#define LDR4_ADC_GPIO_Port GPIOB
#define MPPT_PWM_Pin GPIO_PIN_8
#define MPPT_PWM_GPIO_Port GPIOA
#define CPT_SCL_Pin GPIO_PIN_6
#define CPT_SCL_GPIO_Port GPIOB
#define CPT_SDA_Pin GPIO_PIN_7
#define CPT_SDA_GPIO_Port GPIOB
#define PWM_YAW_1_Pin GPIO_PIN_8
#define PWM_YAW_1_GPIO_Port GPIOB
#define PWM_YAW_2_Pin GPIO_PIN_9
#define PWM_YAW_2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
