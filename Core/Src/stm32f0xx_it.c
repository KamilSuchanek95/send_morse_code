/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f0xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f0308_discovery.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */
typedef uint8_t STATE;
/*.... .- .-.. --- / - ..- / ... . -.- -.-. .--- .- / .--. .. . .-. .-- ... --.. .-*/
uint8_t msg_t[] = {
		1,1,1,1,2,	/* H */
		1,3,2,		/* a */
		1,3,1,1,2,	/* l */
		3,3,3,6,	/* o */
		3,2,		/* t */
		1,1,3,6,	/* u */
		1,1,1,2,	/* s */
		3,2,		/* e */
		3,1,3,2,	/* k */
		3,1,3,1,2,	/* c */
		1,3,3,3,2,	/* j */
		1,3,6,		/* a */
		1,3,3,1,2,	/* p */
		1,1,2,		/* i */
		3,			/* e */
		1,3,1,2,	/* r */
		1,3,3,2,	/* w */
		1,1,1,2,	/* s */
		3,3,1,1,2,	/* z */
		1,3,6		/* a */
};
uint8_t send = 0;
/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LIGHT_OFF 0
#define LIGHT_ON 1
#define WAITING 2
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t el = 0;
int8_t counter = -1;
uint8_t size_of_msg = sizeof(msg_t)/sizeof(msg_t[0]);
STATE state = LIGHT_OFF;
void ziel(){
	switch(el){
	case 1:
		BSP_LED_On(LED_GREEN);
		state = LIGHT_ON;
		el = el - 1;
		break;
	case 3:
		BSP_LED_On(LED_GREEN);
		state = LIGHT_ON;
		el = el - 1;
		break;
	case 2:
		state = WAITING;
		el = el - 1;
		break;
	case 6:
		state = WAITING;
		el = el - 1;
		break;
	}
}
void send_message(){
	switch(state){
	case LIGHT_OFF:
		counter = counter + 1;
		el = msg_t[counter];
		ziel();
		break;
	case LIGHT_ON:
		if(el < 1){
			BSP_LED_Off(LED_GREEN);
			state = LIGHT_OFF;
		}else{
			el = el - 1;
		}
		break;
	case WAITING:
		if(el < 1){
			counter = counter + 1;
			if(counter <= size_of_msg){
				el = msg_t[counter];
				ziel();
			}else{
				send = 0;
			}
		}else{
			el = el - 1;
		}
		break;
	}
}
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */
	if(send > 0) {
		send_message();
	}
	/*BSP_LED_Toggle(LED_GREEN);*/
  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line 0 and 1 interrupts.
  */
void EXTI0_1_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_1_IRQn 0 */
	if(counter>=size_of_msg){
		send = 1;
		state = LIGHT_OFF;
		counter = -1;
	}

  /* USER CODE END EXTI0_1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  /* USER CODE BEGIN EXTI0_1_IRQn 1 */

  /* USER CODE END EXTI0_1_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
