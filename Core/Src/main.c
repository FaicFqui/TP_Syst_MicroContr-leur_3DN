#include "main.h"

/* USER CODE BEGIN Includes */
#define MCP23S17_ADDRESS   0x40  // Adresse SPI du MCP23S17 (A0, A1, A2 = GND)
#define MCP23S17_IODIRA    0x00  // Registre direction PORTA
#define MCP23S17_IODIRB    0x01  // Registre direction PORTB
#define MCP23S17_GPIOA     0x12  // Registre des données PORTA
#define MCP23S17_GPIOB     0x13  // Registre des données PORTB
#define MCP23S17_IOCON     0x0A  // Registre de configuration


extern SPI_HandleTypeDef hspi3;  // SPI3




/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi3;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_SPI3_Init(void);
void MCP23S17_WriteRegister(uint8_t reg, uint8_t value);
/* USER CODE BEGIN PFP */



/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

int __io_putchar(int chr)
{
 HAL_UART_Transmit(&huart2, (uint8_t*)&chr, 1, HAL_MAX_DELAY);
 return chr;
}

// Fonction d'envoi SPI au MCP23S17
void MCP23S17_WriteRegister(uint8_t reg, uint8_t value) {
    uint8_t data[3];
    data[0] = MCP23S17_ADDRESS; // Adresse + bit d'écriture
    data[1] = reg;   // Registre cible
    data[2] = value; // Valeur à écrire

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET); // Activer CS
    HAL_SPI_Transmit(&hspi3, data, 3, HAL_MAX_DELAY); // Transmettre SPI
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);   // Désactiver CS
}

void init_MCP23S17(){
	  // RESET du MCP23S17 via PA0
	      HAL_GPIO_WritePin(GPIOA, VU_nReset_Pin, GPIO_PIN_RESET);
	      HAL_Delay(10);
	      HAL_GPIO_WritePin(GPIOA, VU_nReset_Pin, GPIO_PIN_SET);
	      HAL_Delay(10);

	      // Initialisation du MCP23S17
	      MCP23S17_WriteRegister(MCP23S17_IOCON, 0x08);  // Mode SPI hardware
	      MCP23S17_WriteRegister(MCP23S17_IODIRA, 0x00); // PORTA en sortie (0 = output)
	      MCP23S17_WriteRegister(MCP23S17_IODIRB, 0x00); // PORTB en sortie (0 = output)
	      MCP23S17_WriteRegister(MCP23S17_GPIOA, 0x00);  // Éteindre toutes les LEDs sur PORTA
	      MCP23S17_WriteRegister(MCP23S17_GPIOB, 0x00);  // Éteindre toutes les LEDs sur PORTB

  }

void Chenillard(){
	  for (uint8_t i = 0; i < 16; i++) {
	  	          if (i < 8) {
	  	              // Allumer une LED sur PORTA (GPA0 à GPA7)
	  	              MCP23S17_WriteRegister(MCP23S17_GPIOA, (1 << i)); // Allumer une LED sur PORTA
	  	              MCP23S17_WriteRegister(MCP23S17_GPIOB, 0x00);     // Éteindre toutes les LEDs sur PORTB
	  	          } else {
	  	              // Allumer une LED sur PORTB (GPB0 à GPB7)
	  	              MCP23S17_WriteRegister(MCP23S17_GPIOA, 0x00);     // Éteindre toutes les LEDs sur PORTA
	  	              MCP23S17_WriteRegister(MCP23S17_GPIOB, (1 << (i - 8))); // Allumer une LED sur PORTB
	  	          }
	  	          HAL_Delay(200); // Pause pour l'effet chenillard
	  	      }
 }






int main(void)
{



  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();


  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_SPI3_Init();

  init_MCP23S17();



    printf("\r\n==== Systeme microcontroleur ====\r\n");
    printf("Bonjour via USART!\n"); // Envoi d'un message via l'USART

  while (1) {
	 Chenillard();
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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

	  /* SPI3 parameter configuration*/
	  hspi3.Instance = SPI3;
	  hspi3.Init.Mode = SPI_MODE_MASTER;
	  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
	  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
	  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
	  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
	  hspi3.Init.NSS = SPI_NSS_SOFT;
	  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
	  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
	  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
	  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	  hspi3.Init.CRCPolynomial = 7;
	  hspi3.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
	  hspi3.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
	  if (HAL_SPI_Init(&hspi3) != HAL_OK)
	  {
	    Error_Handler();
	  }


/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }


}


static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};


  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, VU_nReset_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SPI3_nCS_GPIO_Port, SPI3_nCS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : VU_nReset_Pin LD2_Pin */
  GPIO_InitStruct.Pin = VU_nReset_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : SPI3_nCS_Pin */
  GPIO_InitStruct.Pin = SPI3_nCS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SPI3_nCS_GPIO_Port, &GPIO_InitStruct);


}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }

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
