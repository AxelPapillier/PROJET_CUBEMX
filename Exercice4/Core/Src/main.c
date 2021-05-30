/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
	#include<stdio.h>
	#include<stdlib.h>
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
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
void affichage_valeures(int valeur_utilisateur, int valeur_capteur);

void chauffer(int base_temp, int increment);
void refroidir(int base_temp, int increment);

int convert_Temp_utilisateur (int temp_utilisateur[81]);
int convert_Valeur_capteur(int base_temp);


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
char annonce2[200]={'\0'};
int nb;
int valeur_mes ;
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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	
					
  int mess_temp ;
	int valeur_utilisateur;
	int increment;
	char tabC[50] = {0};
	char mess_temp_tab[10] = {'\0'};
	int nb;
	
	int k = 0;
	

	
	
		nb = sprintf(annonce2, "\nVeuillez entrez la temperature souhaite\n\r");
		HAL_UART_Transmit(&huart2, (uint8_t*)annonce2, nb, 1000);
		while (mess_temp_tab[0]=='\0'){
                    HAL_UART_Receive(&huart2, (uint8_t*)mess_temp_tab, sizeof(mess_temp_tab), 2000);
            }
    mess_temp = atoi(mess_temp_tab);//transforme un tableau de char en int
		nb = sprintf(annonce2, "la temperature que vous avez rentre est de %d\n\r", mess_temp);
    HAL_UART_Transmit(&huart2, (uint8_t*)annonce2, nb, 1000);
		srand(mess_temp);	
		int valeur_aleatoire = rand()%4095+0;
		int *base_temp = &valeur_aleatoire;	
		valeur_mes=*base_temp;
						
		convert_Temp_utilisateur(&mess_temp); // Fonction qui convertie la valeur numérique de l'utilisateur en valeur anologique
	  convert_Valeur_capteur(*base_temp);		// Fonction qui 
						
		valeur_utilisateur = convert_Temp_utilisateur(&mess_temp);
		valeur_mes = convert_Valeur_capteur(*base_temp);
		affichage_valeures(valeur_utilisateur, *base_temp);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (k<1)
  {	
		
		increment = mess_temp - valeur_mes;
		
		if ( mess_temp > valeur_mes){
			chauffer(convert_Valeur_capteur(*base_temp), increment);
				}
		
		if (mess_temp < valeur_mes){
			refroidir(convert_Valeur_capteur(*base_temp), increment);	
				}
		
		if (mess_temp == valeur_mes ){
				
			nb = sprintf(tabC, "Le four est a la bonne temperature\n\r");
			HAL_UART_Transmit (&huart2, (uint8_t*)tabC, nb, 100);
		}
			k++;
		
		
		
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
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
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

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_EVEN;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

void affichage_valeures(int valeur_utilisateur, int valeur_capteur){
	char tabC[200] = {0};
	int nb;
	
	nb = sprintf(tabC, "la valeure analogique de l'utilisateur est :%d et la valeure du capteur est: %d\n\r ",valeur_utilisateur, valeur_capteur);
	HAL_UART_Transmit (&huart2, (uint8_t*)tabC, nb, 100);
	HAL_Delay(500);
}

int convert_Temp_utilisateur (int *temp_utilisateur){
		int valeur_temp_utilisateur = 0;
	
		valeur_temp_utilisateur = (*temp_utilisateur * 4095)/200;
		return valeur_temp_utilisateur;
}

int convert_Valeur_capteur(int base_temp){
	int temp_capteur = 0;
	
	temp_capteur = (base_temp*200)/4095;
	return temp_capteur;
}

void chauffer(int base_temp, int increment){
	char tabC[50] = {0};
	int nb;
	
	while(increment > 0){
		increment = increment - 1;
		base_temp++;
		HAL_Delay(1000);
		nb = sprintf(tabC, "la temperature est de %d\n\r",base_temp);
		HAL_UART_Transmit (&huart2, (uint8_t*)tabC, nb, 100);
		HAL_Delay(500);
		valeur_mes = base_temp;
	}
	}
void refroidir(int base_temp, int increment){
	char tabC[50] = {0};
	int nb;
	while(increment < 0){
		increment = increment+1;
		base_temp= base_temp - 1;
		HAL_Delay(1000);
		nb = sprintf(tabC, "la temperature est de %d\n\r",base_temp);
		HAL_UART_Transmit (&huart2, (uint8_t*)tabC, nb, 100);
		HAL_Delay(500);
		valeur_mes = base_temp;

	}
}
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
