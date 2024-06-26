/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : stm32f4xx_hal_msp.c
 * Description        : This file provides code for the MSP Initialization
 *                      and de-Initialization codes.
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
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */
extern DMA_HandleTypeDef hdma_sdio_rx;

extern DMA_HandleTypeDef hdma_sdio_tx;

extern DMA_HandleTypeDef hdma_spi1_rx;

extern DMA_HandleTypeDef hdma_spi1_tx;

extern DMA_HandleTypeDef hdma_spi2_rx;

extern DMA_HandleTypeDef hdma_spi2_tx;

extern DMA_HandleTypeDef hdma_usart6_tx;
/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN Define */

/* USER CODE END Define */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN Macro */

/* USER CODE END Macro */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* External functions --------------------------------------------------------*/
/* USER CODE BEGIN ExternalFunctions */

/* USER CODE END ExternalFunctions */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
/**
 * Initializes the Global MSP.
 */
void HAL_MspInit(void)
{
	/* USER CODE BEGIN MspInit 0 */

	/* USER CODE END MspInit 0 */

	__HAL_RCC_SYSCFG_CLK_ENABLE();
	__HAL_RCC_PWR_CLK_ENABLE();

	/* System interrupt init*/
	/* PendSV_IRQn interrupt configuration */
//	HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0); done by FreeRTOS

	/* USER CODE BEGIN MspInit 1 */

	/* USER CODE END MspInit 1 */
}

/**
 * @brief ADC MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hadc: ADC handle pointer
 * @retval None
 */
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(hadc->Instance==ADC1)
	{
		/* USER CODE BEGIN ADC1_MspInit 0 */

		/* USER CODE END ADC1_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_ADC1_CLK_ENABLE();

		__HAL_RCC_GPIOC_CLK_ENABLE();
		/**ADC1 GPIO Configuration
    PC0     ------> ADC1_IN10
    PC1     ------> ADC1_IN11
    PC2     ------> ADC1_IN12
    PC3     ------> ADC1_IN13
    PC4     ------> ADC1_IN14
    PC5     ------> ADC1_IN15
		 */
		GPIO_InitStruct.Pin = SUPPLY_SENSE_Pin|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
				|GPIO_PIN_4|GPIO_PIN_5;
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		/* USER CODE BEGIN ADC1_MspInit 1 */

		/* USER CODE END ADC1_MspInit 1 */
	}

}

/**
 * @brief ADC MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hadc: ADC handle pointer
 * @retval None
 */
void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{
	if(hadc->Instance==ADC1)
	{
		/* USER CODE BEGIN ADC1_MspDeInit 0 */

		/* USER CODE END ADC1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_ADC1_CLK_DISABLE();

		/**ADC1 GPIO Configuration
    PC0     ------> ADC1_IN10
    PC1     ------> ADC1_IN11
    PC2     ------> ADC1_IN12
    PC3     ------> ADC1_IN13
    PC4     ------> ADC1_IN14
    PC5     ------> ADC1_IN15
		 */
		HAL_GPIO_DeInit(GPIOC, SUPPLY_SENSE_Pin|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
				|GPIO_PIN_4|GPIO_PIN_5);

		/* USER CODE BEGIN ADC1_MspDeInit 1 */

		/* USER CODE END ADC1_MspDeInit 1 */
	}

}

static uint32_t HAL_RCC_CAN1_CLK_ENABLED=0;

/**
 * @brief CAN MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hcan: CAN handle pointer
 * @retval None
 */
void HAL_CAN_MspInit(CAN_HandleTypeDef* hcan)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(hcan->Instance==CAN1)
	{
		/* USER CODE BEGIN CAN1_MspInit 0 */

		/* USER CODE END CAN1_MspInit 0 */
		/* Peripheral clock enable */
		HAL_RCC_CAN1_CLK_ENABLED++;
		if(HAL_RCC_CAN1_CLK_ENABLED==1){
			__HAL_RCC_CAN1_CLK_ENABLE();
		}

		__HAL_RCC_GPIOD_CLK_ENABLE();
		/**CAN1 GPIO Configuration
    PD0     ------> CAN1_RX
    PD1     ------> CAN1_TX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

		/* USER CODE BEGIN CAN1_MspInit 1 */

		/* USER CODE END CAN1_MspInit 1 */
	}
	else if(hcan->Instance==CAN2)
	{
		/* USER CODE BEGIN CAN2_MspInit 0 */

		/* USER CODE END CAN2_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_CAN2_CLK_ENABLE();
		HAL_RCC_CAN1_CLK_ENABLED++;
		if(HAL_RCC_CAN1_CLK_ENABLED==1){
			__HAL_RCC_CAN1_CLK_ENABLE();
		}

		__HAL_RCC_GPIOB_CLK_ENABLE();
		/**CAN2 GPIO Configuration
    PB5     ------> CAN2_RX
    PB6     ------> CAN2_TX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF9_CAN2;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* USER CODE BEGIN CAN2_MspInit 1 */

		/* USER CODE END CAN2_MspInit 1 */
	}

}

/**
 * @brief CAN MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hcan: CAN handle pointer
 * @retval None
 */
void HAL_CAN_MspDeInit(CAN_HandleTypeDef* hcan)
{
	if(hcan->Instance==CAN1)
	{
		/* USER CODE BEGIN CAN1_MspDeInit 0 */

		/* USER CODE END CAN1_MspDeInit 0 */
		/* Peripheral clock disable */
		HAL_RCC_CAN1_CLK_ENABLED--;
		if(HAL_RCC_CAN1_CLK_ENABLED==0){
			__HAL_RCC_CAN1_CLK_DISABLE();
		}

		/**CAN1 GPIO Configuration
    PD0     ------> CAN1_RX
    PD1     ------> CAN1_TX
		 */
		HAL_GPIO_DeInit(GPIOD, GPIO_PIN_0|GPIO_PIN_1);

		/* USER CODE BEGIN CAN1_MspDeInit 1 */

		/* USER CODE END CAN1_MspDeInit 1 */
	}
	else if(hcan->Instance==CAN2)
	{
		/* USER CODE BEGIN CAN2_MspDeInit 0 */

		/* USER CODE END CAN2_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_CAN2_CLK_DISABLE();
		HAL_RCC_CAN1_CLK_ENABLED--;
		if(HAL_RCC_CAN1_CLK_ENABLED==0){
			__HAL_RCC_CAN1_CLK_DISABLE();
		}

		/**CAN2 GPIO Configuration
    PB5     ------> CAN2_RX
    PB6     ------> CAN2_TX
		 */
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_5|GPIO_PIN_6);

		/* USER CODE BEGIN CAN2_MspDeInit 1 */

		/* USER CODE END CAN2_MspDeInit 1 */
	}

}

/**
 * @brief I2C MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hi2c: I2C handle pointer
 * @retval None
 */
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(hi2c->Instance==I2C1)
	{
		/* USER CODE BEGIN I2C1_MspInit 0 */

		/* USER CODE END I2C1_MspInit 0 */

		__HAL_RCC_GPIOB_CLK_ENABLE();
		/**I2C1 GPIO Configuration
    PB7     ------> I2C1_SDA
    PB8     ------> I2C1_SCL
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* Peripheral clock enable */
		__HAL_RCC_I2C1_CLK_ENABLE();
		/* I2C1 interrupt Init */
		HAL_NVIC_SetPriority(I2C1_EV_IRQn, STANDARD_ISR_PRIORITY, 0);
		HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
		HAL_NVIC_SetPriority(I2C1_ER_IRQn, STANDARD_ISR_PRIORITY, 0);
		HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
		/* USER CODE BEGIN I2C1_MspInit 1 */

		/* USER CODE END I2C1_MspInit 1 */
	}
	else if(hi2c->Instance==I2C2)
	{
		/* USER CODE BEGIN I2C2_MspInit 0 */

		/* USER CODE END I2C2_MspInit 0 */

		__HAL_RCC_GPIOB_CLK_ENABLE();
		/**I2C2 GPIO Configuration
    PB10     ------> I2C2_SCL
    PB11     ------> I2C2_SDA
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF4_I2C2;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* Peripheral clock enable */
		__HAL_RCC_I2C2_CLK_ENABLE();
		/* I2C2 interrupt Init */
		HAL_NVIC_SetPriority(I2C2_EV_IRQn, STANDARD_ISR_PRIORITY, 0);
		HAL_NVIC_EnableIRQ(I2C2_EV_IRQn);
		HAL_NVIC_SetPriority(I2C2_ER_IRQn, STANDARD_ISR_PRIORITY, 0);
		HAL_NVIC_EnableIRQ(I2C2_ER_IRQn);
		/* USER CODE BEGIN I2C2_MspInit 1 */

		/* USER CODE END I2C2_MspInit 1 */
	}

}

/**
 * @brief I2C MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hi2c: I2C handle pointer
 * @retval None
 */
void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
{
	if(hi2c->Instance==I2C1)
	{
		/* USER CODE BEGIN I2C1_MspDeInit 0 */

		/* USER CODE END I2C1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_I2C1_CLK_DISABLE();

		/**I2C1 GPIO Configuration
    PB7     ------> I2C1_SDA
    PB8     ------> I2C1_SCL
		 */
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_7);

		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8);

		/* I2C1 interrupt DeInit */
		HAL_NVIC_DisableIRQ(I2C1_EV_IRQn);
		HAL_NVIC_DisableIRQ(I2C1_ER_IRQn);
		/* USER CODE BEGIN I2C1_MspDeInit 1 */

		/* USER CODE END I2C1_MspDeInit 1 */
	}
	else if(hi2c->Instance==I2C2)
	{
		/* USER CODE BEGIN I2C2_MspDeInit 0 */

		/* USER CODE END I2C2_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_I2C2_CLK_DISABLE();

		/**I2C2 GPIO Configuration
    PB10     ------> I2C2_SCL
    PB11     ------> I2C2_SDA
		 */
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10);

		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_11);

		/* I2C2 interrupt DeInit */
		HAL_NVIC_DisableIRQ(I2C2_EV_IRQn);
		HAL_NVIC_DisableIRQ(I2C2_ER_IRQn);
		/* USER CODE BEGIN I2C2_MspDeInit 1 */

		/* USER CODE END I2C2_MspDeInit 1 */
	}

}

/**
 * @brief SD MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hsd: SD handle pointer
 * @retval None
 */
void HAL_SD_MspInit(SD_HandleTypeDef* hsd)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(hsd->Instance==SDIO)
	{
		/* USER CODE BEGIN SDIO_MspInit 0 */

		/* USER CODE END SDIO_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_SDIO_CLK_ENABLE();

		__HAL_RCC_GPIOC_CLK_ENABLE();
		__HAL_RCC_GPIOD_CLK_ENABLE();
		/**SDIO GPIO Configuration
    PC8     ------> SDIO_D0
    PC9     ------> SDIO_D1
    PC10     ------> SDIO_D2
    PC11     ------> SDIO_D3
    PC12     ------> SDIO_CK
    PD2     ------> SDIO_CMD
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF12_SDIO;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_12;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF12_SDIO;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_2;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF12_SDIO;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

		/* SDIO DMA Init */
		/* SDIO_RX Init */
		hdma_sdio_rx.Instance = DMA2_Stream3;
		hdma_sdio_rx.Init.Channel = DMA_CHANNEL_4;
		hdma_sdio_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_sdio_rx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_sdio_rx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_sdio_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
		hdma_sdio_rx.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
		hdma_sdio_rx.Init.Mode = DMA_PFCTRL;
		hdma_sdio_rx.Init.Priority = DMA_PRIORITY_LOW;
		hdma_sdio_rx.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
		hdma_sdio_rx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
		hdma_sdio_rx.Init.MemBurst = DMA_MBURST_INC4;
		hdma_sdio_rx.Init.PeriphBurst = DMA_PBURST_INC4;
		if (HAL_DMA_Init(&hdma_sdio_rx) != HAL_OK)
		{
			Error_Handler();
		}

		__HAL_LINKDMA(hsd,hdmarx,hdma_sdio_rx);

		/* SDIO_TX Init */
		hdma_sdio_tx.Instance = DMA2_Stream6;
		hdma_sdio_tx.Init.Channel = DMA_CHANNEL_4;
		hdma_sdio_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
		hdma_sdio_tx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_sdio_tx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_sdio_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
		hdma_sdio_tx.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
		hdma_sdio_tx.Init.Mode = DMA_PFCTRL;
		hdma_sdio_tx.Init.Priority = DMA_PRIORITY_LOW;
		hdma_sdio_tx.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
		hdma_sdio_tx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
		hdma_sdio_tx.Init.MemBurst = DMA_MBURST_INC4;
		hdma_sdio_tx.Init.PeriphBurst = DMA_PBURST_INC4;
		if (HAL_DMA_Init(&hdma_sdio_tx) != HAL_OK)
		{
			Error_Handler();
		}

		__HAL_LINKDMA(hsd,hdmatx,hdma_sdio_tx);

		/* SDIO interrupt Init */
		HAL_NVIC_SetPriority(SDIO_IRQn, SDIO_ISR_PRIORITY, 0);
		HAL_NVIC_EnableIRQ(SDIO_IRQn);
		/* USER CODE BEGIN SDIO_MspInit 1 */

		/* USER CODE END SDIO_MspInit 1 */
	}

}

/**
 * @brief SD MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hsd: SD handle pointer
 * @retval None
 */
void HAL_SD_MspDeInit(SD_HandleTypeDef* hsd)
{
	if(hsd->Instance==SDIO)
	{
		/* USER CODE BEGIN SDIO_MspDeInit 0 */

		/* USER CODE END SDIO_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_SDIO_CLK_DISABLE();

		/**SDIO GPIO Configuration
    PC8     ------> SDIO_D0
    PC9     ------> SDIO_D1
    PC10     ------> SDIO_D2
    PC11     ------> SDIO_D3
    PC12     ------> SDIO_CK
    PD2     ------> SDIO_CMD
		 */
		HAL_GPIO_DeInit(GPIOC, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
				|GPIO_PIN_12);

		HAL_GPIO_DeInit(GPIOD, GPIO_PIN_2);

		/* SDIO DMA DeInit */
		HAL_DMA_DeInit(hsd->hdmarx);
		HAL_DMA_DeInit(hsd->hdmatx);

		/* SDIO interrupt DeInit */
		HAL_NVIC_DisableIRQ(SDIO_IRQn);
		/* USER CODE BEGIN SDIO_MspDeInit 1 */

		/* USER CODE END SDIO_MspDeInit 1 */
	}

}

/**
 * @brief SPI MSP Initialization
 * This function configures the hardware resources used in this example
 * @param hspi: SPI handle pointer
 * @retval None
 */
void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(hspi->Instance==SPI1)
	{
		/* USER CODE BEGIN SPI1_MspInit 0 */

		/* USER CODE END SPI1_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_SPI1_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**SPI1 GPIO Configuration
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* SPI1 DMA Init */
		/* SPI1_RX Init */
		hdma_spi1_rx.Instance = DMA2_Stream0;
		hdma_spi1_rx.Init.Channel = DMA_CHANNEL_3;
		hdma_spi1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_spi1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_spi1_rx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_spi1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_spi1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_spi1_rx.Init.Mode = DMA_NORMAL;
		hdma_spi1_rx.Init.Priority = DMA_PRIORITY_LOW;
		hdma_spi1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		if (HAL_DMA_Init(&hdma_spi1_rx) != HAL_OK)
		{
			Error_Handler();
		}

		__HAL_LINKDMA(hspi,hdmarx,hdma_spi1_rx);

		/* SPI1_TX Init */
		hdma_spi1_tx.Instance = DMA2_Stream5;
		hdma_spi1_tx.Init.Channel = DMA_CHANNEL_3;
		hdma_spi1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
		hdma_spi1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_spi1_tx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_spi1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_spi1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_spi1_tx.Init.Mode = DMA_NORMAL;
		hdma_spi1_tx.Init.Priority = DMA_PRIORITY_LOW;
		hdma_spi1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		if (HAL_DMA_Init(&hdma_spi1_tx) != HAL_OK)
		{
			Error_Handler();
		}

		__HAL_LINKDMA(hspi,hdmatx,hdma_spi1_tx);

		/* USER CODE BEGIN SPI1_MspInit 1 */

		/* USER CODE END SPI1_MspInit 1 */
	}
	else if(hspi->Instance==SPI2)
	{
		/* USER CODE BEGIN SPI2_MspInit 0 */

		/* USER CODE END SPI2_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_SPI2_CLK_ENABLE();

		__HAL_RCC_GPIOB_CLK_ENABLE();
		/**SPI2 GPIO Configuration
    PB13     ------> SPI2_SCK
    PB14     ------> SPI2_MISO
    PB15     ------> SPI2_MOSI
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* SPI2 DMA Init */
		/* SPI2_RX Init */
		hdma_spi2_rx.Instance = DMA1_Stream3;
		hdma_spi2_rx.Init.Channel = DMA_CHANNEL_0;
		hdma_spi2_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_spi2_rx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_spi2_rx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_spi2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_spi2_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_spi2_rx.Init.Mode = DMA_NORMAL;
		hdma_spi2_rx.Init.Priority = DMA_PRIORITY_LOW;
		hdma_spi2_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		if (HAL_DMA_Init(&hdma_spi2_rx) != HAL_OK)
		{
			Error_Handler();
		}

		__HAL_LINKDMA(hspi,hdmarx,hdma_spi2_rx);

		/* SPI2_TX Init */
		hdma_spi2_tx.Instance = DMA1_Stream4;
		hdma_spi2_tx.Init.Channel = DMA_CHANNEL_0;
		hdma_spi2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
		hdma_spi2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_spi2_tx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_spi2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_spi2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_spi2_tx.Init.Mode = DMA_NORMAL;
		hdma_spi2_tx.Init.Priority = DMA_PRIORITY_LOW;
		hdma_spi2_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		if (HAL_DMA_Init(&hdma_spi2_tx) != HAL_OK)
		{
			Error_Handler();
		}

		__HAL_LINKDMA(hspi,hdmatx,hdma_spi2_tx);

		/* USER CODE BEGIN SPI2_MspInit 1 */

		/* USER CODE END SPI2_MspInit 1 */
	}

}

/**
 * @brief SPI MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param hspi: SPI handle pointer
 * @retval None
 */
void HAL_SPI_MspDeInit(SPI_HandleTypeDef* hspi)
{
	if(hspi->Instance==SPI1)
	{
		/* USER CODE BEGIN SPI1_MspDeInit 0 */

		/* USER CODE END SPI1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_SPI1_CLK_DISABLE();

		/**SPI1 GPIO Configuration
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI
		 */
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

		/* SPI1 DMA DeInit */
		HAL_DMA_DeInit(hspi->hdmarx);
		HAL_DMA_DeInit(hspi->hdmatx);
		/* USER CODE BEGIN SPI1_MspDeInit 1 */

		/* USER CODE END SPI1_MspDeInit 1 */
	}
	else if(hspi->Instance==SPI2)
	{
		/* USER CODE BEGIN SPI2_MspDeInit 0 */

		/* USER CODE END SPI2_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_SPI2_CLK_DISABLE();

		/**SPI2 GPIO Configuration
    PB13     ------> SPI2_SCK
    PB14     ------> SPI2_MISO
    PB15     ------> SPI2_MOSI
		 */
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);

		/* SPI2 DMA DeInit */
		HAL_DMA_DeInit(hspi->hdmarx);
		HAL_DMA_DeInit(hspi->hdmatx);
		/* USER CODE BEGIN SPI2_MspDeInit 1 */

		/* USER CODE END SPI2_MspDeInit 1 */
	}

}

/**
 * @brief UART MSP Initialization
 * This function configures the hardware resources used in this example
 * @param huart: UART handle pointer
 * @retval None
 */
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(huart->Instance==UART4)
	{
		/* USER CODE BEGIN UART4_MspInit 0 */

		/* USER CODE END UART4_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_UART4_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**UART4 GPIO Configuration
    PA0-WKUP     ------> UART4_TX
    PA1     ------> UART4_RX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USER CODE BEGIN UART4_MspInit 1 */

		/* USER CODE END UART4_MspInit 1 */
	}
	else if(huart->Instance==USART1)
	{
		/* USER CODE BEGIN USART1_MspInit 0 */

		/* USER CODE END USART1_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_USART1_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USER CODE BEGIN USART1_MspInit 1 */

		/* USER CODE END USART1_MspInit 1 */
	}
	else if(huart->Instance==USART2)
	{
		/* USER CODE BEGIN USART2_MspInit 0 */

		/* USER CODE END USART2_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_USART2_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USER CODE BEGIN USART2_MspInit 1 */

		/* USER CODE END USART2_MspInit 1 */
	}
	else if(huart->Instance==USART3)
	{
		/* USER CODE BEGIN USART3_MspInit 0 */
		/* Handled in usart3_driver.cpp*/
		/* USER CODE END USART3_MspInit 0 */
		/* Peripheral clock enable */
		//__HAL_RCC_USART3_CLK_ENABLE();

		//__HAL_RCC_GPIOD_CLK_ENABLE();
		/**USART3 GPIO Configuration
    PD8     ------> USART3_TX
    PD9     ------> USART3_RX
		 */
		//GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
		//GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		//GPIO_InitStruct.Pull = GPIO_NOPULL;
		//GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		//GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
		//HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

		/* USER CODE BEGIN USART3_MspInit 1 */

		/* USER CODE END USART3_MspInit 1 */
	}
	else if(huart->Instance==USART6)
	{
		/* USER CODE BEGIN USART6_MspInit 0 */

		/* USER CODE END USART6_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_USART6_CLK_ENABLE();

		__HAL_RCC_GPIOC_CLK_ENABLE();
		/**USART6 GPIO Configuration
    PC6     ------> USART6_TX
    PC7     ------> USART6_RX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		/* USART6 DMA Init */
		/* USART6_TX Init */
		hdma_usart6_tx.Instance = DMA2_Stream7;
		hdma_usart6_tx.Init.Channel = DMA_CHANNEL_5;
		hdma_usart6_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
		hdma_usart6_tx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_usart6_tx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_usart6_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_usart6_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_usart6_tx.Init.Mode = DMA_NORMAL;
		hdma_usart6_tx.Init.Priority = DMA_PRIORITY_LOW;
		hdma_usart6_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		if (HAL_DMA_Init(&hdma_usart6_tx) != HAL_OK)
		{
			Error_Handler();
		}

		__HAL_LINKDMA(huart,hdmatx,hdma_usart6_tx);

		/* USART6 interrupt Init */
		HAL_NVIC_SetPriority(USART6_IRQn, STANDARD_ISR_PRIORITY, 0);
		HAL_NVIC_EnableIRQ(USART6_IRQn);
		/* USER CODE BEGIN USART6_MspInit 1 */

		/* USER CODE END USART6_MspInit 1 */
	}

}

/**
 * @brief UART MSP De-Initialization
 * This function freeze the hardware resources used in this example
 * @param huart: UART handle pointer
 * @retval None
 */
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
	if(huart->Instance==UART4)
	{
		/* USER CODE BEGIN UART4_MspDeInit 0 */

		/* USER CODE END UART4_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_UART4_CLK_DISABLE();

		/**UART4 GPIO Configuration
    PA0-WKUP     ------> UART4_TX
    PA1     ------> UART4_RX
		 */
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0|GPIO_PIN_1);

		/* USER CODE BEGIN UART4_MspDeInit 1 */

		/* USER CODE END UART4_MspDeInit 1 */
	}
	else if(huart->Instance==USART1)
	{
		/* USER CODE BEGIN USART1_MspDeInit 0 */

		/* USER CODE END USART1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART1_CLK_DISABLE();

		/**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
		 */
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

		/* USER CODE BEGIN USART1_MspDeInit 1 */

		/* USER CODE END USART1_MspDeInit 1 */
	}
	else if(huart->Instance==USART2)
	{
		/* USER CODE BEGIN USART2_MspDeInit 0 */

		/* USER CODE END USART2_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART2_CLK_DISABLE();

		/**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
		 */
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

		/* USER CODE BEGIN USART2_MspDeInit 1 */

		/* USER CODE END USART2_MspDeInit 1 */
	}
	else if(huart->Instance==USART3)
	{
		/* USER CODE BEGIN USART3_MspDeInit 0 */

		/* USER CODE END USART3_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART3_CLK_DISABLE();

		/**USART3 GPIO Configuration
    PD8     ------> USART3_TX
    PD9     ------> USART3_RX
		 */
		HAL_GPIO_DeInit(GPIOD, GPIO_PIN_8|GPIO_PIN_9);

		/* USER CODE BEGIN USART3_MspDeInit 1 */

		/* USER CODE END USART3_MspDeInit 1 */
	}
	else if(huart->Instance==USART6)
	{
		/* USER CODE BEGIN USART6_MspDeInit 0 */

		/* USER CODE END USART6_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART6_CLK_DISABLE();

		/**USART6 GPIO Configuration
    PC6     ------> USART6_TX
    PC7     ------> USART6_RX
		 */
		HAL_GPIO_DeInit(GPIOC, GPIO_PIN_6|GPIO_PIN_7);

		/* USART6 DMA DeInit */
		HAL_DMA_DeInit(huart->hdmatx);

		/* USART6 interrupt DeInit */
		HAL_NVIC_DisableIRQ(USART6_IRQn);
		/* USER CODE BEGIN USART6_MspDeInit 1 */

		/* USER CODE END USART6_MspDeInit 1 */
	}

}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
