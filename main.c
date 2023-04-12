/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "STM32F4xx.h"

//Asciiname (ali!murat) =896
//ASciisurname (kurtulan)= 886
//ASciitotal(ali!murat!kurtulan)=1815
//Timernumber = 10
//Duration= 26580
//LEDPINNUMBER =PN15

int count=0;
int hedef=26580;
int anlikdeger=0;
int ilkdeger=0;
int degerfark=0;


void GPIO_Config()
{
(*((int*)0xE000ED88))|=0x0F00000;
RCC->AHB1ENR |= 0x00000009;
GPIOD->MODER = 0x40000000;
GPIOA->OSPEEDR= 0xFFFFFFFF;
GPIOD->OSPEEDR= 0xFFFFFFFF;
GPIOA->PUPDR = 0x00000000;
}

void Timer_Config()
{
RCC->APB2ENR |= 0x00020000;
TIM10->PSC=0X0002;
TIM10->ARR=(uint32_t)1680;
TIM10->CR1=0x0001;
TIM10->CNT=0X0000;

}

void delayy(){

	    ilkdeger = TIM10->CNT;
	    while(count < hedef)
	    {
	        anlikdeger = TIM10->CNT;
	        if(anlikdeger < ilkdeger)
	        {
	            degerfark = (hedef - ilkdeger) + anlikdeger;
	        }
	        else
	        {
	            degerfark = anlikdeger - ilkdeger;
	        }
	        count += degerfark;
	        ilkdeger = anlikdeger;
	    }
	}



int main()
{


	GPIO_Config();

	Timer_Config();

while(1){


{
 GPIOD->ODR=0X00008000;
 delayy();

}


}
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
