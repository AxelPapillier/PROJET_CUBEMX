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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
	struct utilisateur{
			char identifiant[30];
			char password[30];
			char type_encode[5];
			};
	void capteur();
	void affichage_valeures(int valeur_utilisateur, int valeur_capteur);
	void chauffer(int base_temp, int increment);
	void refroidir(int base_temp, int increment);
	int valeur_mes ;
	int nb1;
	int convert_Temp_utilisateur (int temp_utilisateur[81]);
	int convert_Valeur_capteur(int base_temp);
	char *cesarASCII_chiffre(char* dst, int taille_dst, char* src, struct utilisateur *list);
	char *apply_xor8(char* dst, int taille_dst, char* src, unsigned char cle, struct utilisateur *list);
	char annonce2[200]={'\0'};
	
	int menu(int i, struct utilisateur *list);
	int inscription(int i, struct utilisateur *list);
	void connexion(int i, struct utilisateur *list);
	int strcmp(const char *str1, const char *str2);
	unsigned char *base64_encode(unsigned char *dst, int size, char *src, struct utilisateur *list);
	void menu2(int i, struct utilisateur *list);
	static const char tab[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";	
	
	char annonce[200]={'\0'};
	int nb;
	int valeur_de_i=0;
	int clefAscii;
	int clefXOR;
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
		int i =0;
    struct utilisateur list [10];

    while (i != -1)
        i = menu(i, list);
    return 0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  
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
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

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
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
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
int menu(int i, struct utilisateur *list)
{
	char choix_tab[10]={'\0'};
	int choix;
	
	for(int k = 0; annonce[k] != '\0'; k++)
		annonce[k] = '\0';
	nb = sprintf(annonce, "\n\rBienvenue ! Veuillez selectioner une des option :\n\n\r0. Quitter le programme\n\r1. S'inscrire\n\r2. Se connecter\n\n\n\r");
	HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 1000);
	i = valeur_de_i;
	while (choix_tab[0]=='\0'){
					HAL_UART_Receive(&huart2, (uint8_t*)choix_tab, sizeof(choix_tab), 100);
			}
	choix = atoi(choix_tab);//transforme un tableau de char en int
			
	switch (choix)
	{
			case 0: 
				nb = sprintf(annonce, "Au revoir !\n\r");
				HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 100);
				return -1;
			case 1:
					if (i < 10)//car 10 maximum
					{
							valeur_de_i = inscription(i, list);
					}
					else
					{
							nb = sprintf(annonce, "Desole il y a trop d'inscrits\n\r");
							HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 100);
					}
					break;
			case 2:
					connexion(i, list);
					break;
			default : 
					nb = sprintf(annonce, "default menu2\n\r");
					HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 100);
					break;
	
	}
	return i;
}
void capteur(){
		int mess_temp ;
		int valeur_utilisateur;
		int increment;
		char tabC[50] = {0};
		char mess_temp_tab[10] = {'\0'};
		int nb;
		int k = 0;
	
		nb1 = sprintf(annonce2, "\nVeuillez entrez la temperature souhaite\n\r");
		HAL_UART_Transmit(&huart2, (uint8_t*)annonce2, nb1, 1000);
		while (mess_temp_tab[0]=='\0'){
                    HAL_UART_Receive(&huart2, (uint8_t*)mess_temp_tab, sizeof(mess_temp_tab), 2000);
            }
    mess_temp = atoi(mess_temp_tab);//transforme un tableau de char en int
		nb1 = sprintf(annonce2, "la temperature que vous avez rentre est de %dC\n\r", mess_temp);
    HAL_UART_Transmit(&huart2, (uint8_t*)annonce2, nb1, 1000);
		srand(mess_temp);	
		int valeur_aleatoire = rand()%4095+0;
		int *base_temp = &valeur_aleatoire;	
		valeur_mes=*base_temp;
						
		convert_Temp_utilisateur(&mess_temp); // Fonction qui convertie la valeur numérique de l'utilisateur en valeur anologique
	  convert_Valeur_capteur(*base_temp);		// Fonction qui 
						
		valeur_utilisateur = convert_Temp_utilisateur(&mess_temp);
		valeur_mes = convert_Valeur_capteur(*base_temp);
		affichage_valeures(valeur_utilisateur, *base_temp);
		
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
		}
}

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

int inscription(int i, struct utilisateur *list)
{
	int size;
	char mdp_encode_ascii[81]= {'\0'};
	char mdp_encode_xor[81]= {'\0'};
	unsigned char *encode = NULL;
	nb = sprintf(annonce, "Veuillez entrer un identifiant : \n\r");
	HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 100);
	
	while (list[i].identifiant[0]=='\0'){
			HAL_UART_Receive(&huart2, (uint8_t*)list[i].identifiant, sizeof(list[i].identifiant), 5000);
	}
	nb = sprintf(annonce, "Veuillez entrer mot de passe : \n\r");
	HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 1000);
		
	while (list[i].password[0]=='\0'){
			HAL_UART_Receive(&huart2, (uint8_t*)list[i].password, sizeof(list[i].password), 5000);
	}
	nb = sprintf(annonce, "\n\nidentifiant : %s password : %s\n\n\r", list[i].identifiant, list[i].password);
	HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 100);
	srand(list[i].password[0]+i*rand());
	
	clefAscii = rand()%95;
	clefXOR = rand()%255;
	
	nb = sprintf(annonce, "\nclef xor: %d\n\n\r", clefXOR);
	HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 100);
	
	size = 4 * ((strlen(list[i].password) + 2) / 3);
	base64_encode(encode, size, list[i].password, list);
	free(encode);
	nb = sprintf(annonce, "\npassword encode base64: %s\n\n\r", list[i].password);
	HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 100);
	
	nb = sprintf(annonce, "Choisissez votre type d'encodage (cesar 'c' ou XOR 'x' : \n\r");
	HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 100);
	
	while (list[i].type_encode[0]=='\0'){
			HAL_UART_Receive(&huart2, (uint8_t*)list[i].type_encode, sizeof(list[i].type_encode), 500);
	}
	
	if (list[i].type_encode[0] == 'c')
	{
		cesarASCII_chiffre(mdp_encode_ascii, 81,  list[i].password, list);
		nb = sprintf(annonce, "\n\rpassword encode ascii: %s\n\n\r", list[i].password);
		HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 100);
	}
	if (list[i].type_encode[0] == 'x')
	{
		nb = sprintf(annonce, "\n\rpassword encode XOR: ");
		HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 1000);
		apply_xor8(mdp_encode_xor, 81, list[i].password, clefXOR, list);
		for (int p = 0; list[i].password[p] != '\0'; p++)
		{
			nb = sprintf(annonce, "%x ", list[i].password[p]);
			HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 1000);
		}
	}
	i = i + 1;
	return i;
}

void connexion(int i, struct utilisateur *list)
{
		char mdp_encode_ascii[81]= {'\0'};
		char mdp_encode_xor[81]= {'\0'};
		int size;
		unsigned char *encode = NULL;
    char identifiant[30]={'\0'};
    char password[30]={'\0'};
    int j=0;
    int p = 1;
    int erreur = 0;
		int correct = 0;
		int k = 0;

    while (p != 0){
        nb = sprintf(annonce, "Veuillez entrer votre identifiant : \n\r");
				HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 1000);
				while (identifiant[0]=='\0'){
				HAL_UART_Receive(&huart2, (uint8_t*)identifiant, sizeof(identifiant), 5000);
				}
        for (j = 0; j < i; j++)
        {
            if (strcmp(identifiant, list[j].identifiant) == 0){
								nb = sprintf(annonce, "\n\rBonjour %s !\n\r", identifiant);
								HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 1000);
								k=j;//prend la valeur de de l'indice de l'identifiant 
							
                while (correct != -1){
										nb = sprintf(annonce, "Entrez votre mot de passe\n\r");
										HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 100);
                    p = 0;
										while (password[0]=='\0'){
											HAL_UART_Receive(&huart2, (uint8_t*)password, sizeof(password), 5000);
										}
										size = 4 * ((strlen(password) + 2) / 3);
										base64_encode(encode, size, password, list);
										free(encode);
										if (list[k].type_encode[0] == 'c')
										{
											cesarASCII_chiffre(mdp_encode_ascii, 81,  password, list);
										}
										if (list[k].type_encode[0] == 'x')
										{
											apply_xor8(mdp_encode_xor, 81, password, clefXOR, list);
										}
											
										if (strcmp(password, list[k].password) == 0)
										{
											
											menu2(i, list);	
											correct = -1;
											p = 0;
											for (j = 0; j < 30; j++)
											{
												identifiant[j]='\0';
												password[j]='\0';
											}
											return;
										}
										else
										{
											nb = sprintf(annonce, "faux  ");
											HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 100);
											erreur++;
											for (j = 0; j < 30; j++)
											{
												identifiant[j]='\0';
												password[j]='\0';
											}
										}
								
										if (erreur == 3){
											nb = sprintf(annonce, "trop d'erreur retour au menun\r");
											HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 100);
											for (j = 0; j < 30; j++)
											{
												identifiant[j]='\0';
												password[j]='\0';
											}
											menu(i, list);	
											return;
										}
               }
						}
            else
            {
								if(j == i){
								nb = sprintf(annonce, "Identifiant introuvable -> ");
								HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 100);
								}
            }
        }
				p = 1;
				for (j = 0; j < 30; j++)
				{
					identifiant[j]='\0';
					password[j]='\0';
				}
    }
		return;
}
void menu2(int i, struct utilisateur *list)
{
	char choix_tab[10]={'\0'};
	int choix;
	
	nb = sprintf(annonce, "\n\n\rConnexion reussie, veuillez selectioner une des option :\n\n\r0. deconnexion\n\r1. Regler la temperature de votre four\n\r");
	HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 1000);
	
	while (choix_tab[0]=='\0'){
					HAL_UART_Receive(&huart2, (uint8_t*)choix_tab, sizeof(choix_tab), 100);
			}
	choix = atoi(choix_tab);
	
	switch (choix)
	{
			case 0: menu(i, list);
					break;
			case 1:
					capteur();
					break;
			default : 
					nb = sprintf(annonce, "default menu2\n\r");
					HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 100);
					break;
	}
	return;
}
unsigned char *base64_encode(unsigned char *dst, int size, char *src, struct utilisateur *list)
{
    static int mod_table[] = {0, 2, 1};
    int str_size = strlen(src);
    int i = 0;
    int j = 0;
    int oct_a = 0;
    int oct_b = 0;
    int oct_c = 0;
    int triple = 0;

    dst = malloc(sizeof(char) * (size+1));
    for (; i < str_size;) {
        oct_a = i < str_size ? src[i++] : 0;            //si i < str_size alors oct_a = src[i++] else oct_a = 0
        oct_b = i < str_size ? src[i++] : 0;
        oct_c = i < str_size ? src[i++] : 0;
        triple = (oct_a << 16) + (oct_b << 8) + oct_c;
        dst[j++] = tab[(triple >> 18) & 63];
        dst[j++] = tab[(triple >> 12) & 63];
        dst[j++] = tab[(triple >> 6) & 63];
        dst[j++] = tab[(triple) & 63];
    }

    for (i = 0; i < mod_table[size % 3]; i++)
        dst[size-1 - i] = '=';
    dst[size] = '\0';
		for (int k = 0; dst [k] !='\0'; k++)
        src[k] = dst[k];
    return (dst);
}

char *cesarASCII_chiffre(char* dst, int taille_dst, char* src, struct utilisateur *list)
{
    int j=0;
    int rang;
		
		nb = sprintf(annonce, "clef = %d\n\r", clefAscii);
		HAL_UART_Transmit(&huart2, (uint8_t*)annonce, nb, 1000);

    while(src[j] != '\0')
    {
            rang = src[j] - 32;
            rang = (rang + clefAscii) % 95;
            if(rang < 0) rang += 95;
            dst[j] = 32 + rang;
   
        j++;
    }
    dst[j] = '\0';
		

		for (int k = 0; dst [k] !='\0'; k++)
        src[k] = dst[k];
    return (dst);
}
char *apply_xor8(char* dst, int taille_dst, char* src, unsigned char cle, struct utilisateur *list)
{
    int j;

    for (j=0; src[j]!='\0'; j++)
    {
			dst[j] = src[j]^cle;
			src[j] = dst[j];
    }
		for (int k = 0; dst[k] !='\0'; k++)
        src[k] = dst[k];
    return (dst);
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