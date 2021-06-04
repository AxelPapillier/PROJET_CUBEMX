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
#include<string.h>
#include <ctype.h>
#include<stdlib.h>
#include<time.h>

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
int toupper(int c);
int cesar26_chiffre(char* dst, int taille_dst, char* src);
int cesar26_dechiffre(char* dst, int taille_dst, char* src);
int cesarASCII_chiffre(char* dst, int taille_dst, char* src);
int cesarASCII_dechiffre(char* dst, int taille_dst, char* src);
int apply_xor8(char* dst, int taille_dst, char* src, unsigned char cle);
char annonce[50] = {0};
int nb;
int clef;
int clefXOR;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	char mdp[81]= {'\0'};
	char mdp_encode[81]= {'\0'};
	char mdp_decode[81]= {'\0'};
	int i;

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
	nb = sprintf(annonce, "Veuillez entrer votre mot de passe\n\r");
	HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 1000);
	
	while (mdp[0]=='\0'){
					HAL_UART_Receive(&huart2, (uint8_t*)mdp, sizeof(mdp), 5000);
			}
	
	for (i=0; mdp[i]!='\0'; i++);//trouver la taille
	srand(mdp[0]+i*rand());//srand depend du premier caractere de la chaine + de la taille 
	clef = rand()%26;
	srand(mdp[0]+i*rand());//srand depend du premier caractere de la chaine + de la taille 
	clefXOR = rand()%255;
	nb = sprintf(annonce, "%s\n\r", mdp);
	HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 1000);		
	//cesar26_chiffre(mdp_encode, 81, mdp);
	//cesar26_dechiffre(mdp_decode, 81, mdp_encode);
	//cesarASCII_chiffre (mdp_encode, 81, mdp);
  //cesarASCII_dechiffre (mdp_decode, 81, mdp_encode);
	apply_xor8(mdp_encode, 81, mdp, clefXOR);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
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
  huart2.Init.WordLength = UART_WORDLENGTH_9B;
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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */
int cesar26_chiffre(char* dst, int taille_dst, char* src)
{
    int i;
    int j=0;
    int rang;

    for (i = 0; src[i] != '\0'; i++)
    {
       src[i] = toupper(src[i]); //maintenant, chaine tout en maj, on peut commencer l'encodage
    }
   
		//nb = sprintf(annonce, "Veuillez entrer la cle d'encodage\n\r");
		//HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 1000);
 
		nb = sprintf(annonce, "clef = %d\n\r", clef);
		HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 1000);
		
    while(src[j] != '\0')
    {
        if (src[j] >= 'A' && src[j] <= 'Z' ){
            rang = src[j] - 'A';
            rang = (rang + clef) % 26;
            if(rang < 0) rang += 26;
            dst[j] = 'A' + rang;
        }
        else {
            dst[j] = src[j];
        }
        j++;
    }
    dst[j] = '\0';
		
		nb = sprintf(annonce, "MDP encode : %s\n\r", dst);
		HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 1000);
		
    return 0;
}

int cesar26_dechiffre(char* dst, int taille_dst, char* src)
{
    int i;
    int j=0;
    int rang;

		nb = sprintf(annonce, "clef = %d\n\r", clef);
		HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 1000);
	
    while(src[j] != '\0')
    {
        if (src[j] >= 'A' && src[j] <= 'Z' ){
            rang = src[j] - 'A';
            rang = (rang - clef) % 26;
            if(rang < 0) rang += 26;
            dst[j] = 'A' + rang;
        }
        else {
            dst[j] = src[j];
        }
        j++;
    }
    dst[j] = '\0';
		
    nb = sprintf(annonce, "MDP decode : %s\n\r", dst);
		HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 1000);
		
    return 0;
}

int cesarASCII_chiffre(char* dst, int taille_dst, char* src)
{
    int i;
    int j=0;
    int rang;

		nb = sprintf(annonce, "clef = %d\n\r", clef);
		HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 1000);

    while(src[j] != '\0')
    {
            rang = src[j] - 32;
            rang = (rang + clef) % 95;
            if(rang < 0) rang += 95;
            dst[j] = 32 + rang;
   
        j++;
    }
    dst[j] = '\0';
		
		nb = sprintf(annonce, "MDP encode : %s\n\r", dst);
		HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 1000);
		
    return 0;
}

int cesarASCII_dechiffre(char* dst, int taille_dst, char* src)
{
    int i;
    int j=0;
    int rang;

		nb = sprintf(annonce, "clef = %d\n\r", clef);
		HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 1000);

    while(src[j] != '\0')
    {
            rang = src[j] - 32;
            rang = (rang - clef) % 95;
            if(rang < 0) rang += 95;
            dst[j] = 32 + rang;

        j++;
    }
    dst[j] = '\0';
		
    nb = sprintf(annonce, "MDP decode : %s\n\r", dst);
		HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 1000);
		
    return 0;
}
int apply_xor8(char* dst, int taille_dst, char* src, unsigned char cle)
{
    int j,i;
    unsigned char y;
    unsigned char decode[50];
		nb = sprintf(annonce, "\n\r cle = %d ", cle);
		HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 1000);
    nb = sprintf(annonce, "MDP encode : ");
		HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 1000);
	
    for (j=0; src[j]!='\0'; j++)
    {
				nb = sprintf(annonce, "\n\rsrc = %c ", src[j]);
				HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 1000);
        y = src[j]^cle;
				dst[j] = y;
				nb = sprintf(annonce, "\n\r%x ", dst[j]);
				HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 1000);
    }
    nb = sprintf(annonce, "MDP decode : ");
		HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 1000);
    for (i=0; dst[i]!='\0'; i++)
    {
        decode [i] = dst[i]^cle;
				nb = sprintf(annonce, "%c ", decode[i]);
				HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 1000);
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
