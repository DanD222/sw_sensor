/** *****************************************************************************
 * @file    	usart1_driver.cpp
 * @brief   	Driver for DMA transmission using USART 1
 * @author  	Dr. Klaus Schaefer
 * @copyright 	Copyright 2021 Dr. Klaus Schaefer. All rights reserved.
 * @license 	This project is released under the GNU Public License GPL-3.0

    <Larus Flight Sensor Firmware>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************************/
#include "system_configuration.h"
#include "main.h"
#include "FreeRTOS_wrapper.h"
#include "stm32f4xx_hal.h"
#include "GNSS.h"
#include "usart_1_driver.h"

COMMON UART_HandleTypeDef huart1;
COMMON DMA_HandleTypeDef hdma_USART_1_TX;

static COMMON uint8_t uart1_rx_byte = 0;
static COMMON QueueHandle_t UART1_Rx_Queue = NULL;
#define UART1_RX_QUEUE_SIZE 128
#if RUN_USART_1_TEST
COMMON static TaskHandle_t USART_1_task_ID = NULL;
#endif

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
void USART_1_Init (void)
{
  if (UART1_Rx_Queue == NULL)
    {
      UART1_Rx_Queue =  xQueueCreate(UART1_RX_QUEUE_SIZE, sizeof(uint8_t));
    }
  ASSERT(UART1_Rx_Queue);

  GPIO_InitTypeDef GPIO_InitStruct = { 0 };
  __HAL_RCC_USART1_CLK_ENABLE();

  __HAL_RCC_GPIOA_CLK_ENABLE();
  /**USART1 GPIO Configuration
   PA9     ------> USART1_TX
   PA10     ------> USART1_RX
   */
  GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
  HAL_GPIO_Init (GPIOA, &GPIO_InitStruct);

  hdma_USART_1_TX.Instance = DMA2_Stream7;
  hdma_USART_1_TX.Init.Channel = DMA_CHANNEL_4;
  hdma_USART_1_TX.Init.Direction = DMA_MEMORY_TO_PERIPH;
  hdma_USART_1_TX.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_USART_1_TX.Init.MemInc = DMA_MINC_ENABLE;
  hdma_USART_1_TX.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_USART_1_TX.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
  hdma_USART_1_TX.Init.Mode = DMA_NORMAL;
  hdma_USART_1_TX.Init.Priority = DMA_PRIORITY_LOW;
  hdma_USART_1_TX.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
  if (HAL_DMA_Init (&hdma_USART_1_TX) != HAL_OK)
    {
      ASSERT(0);
    }

  HAL_NVIC_SetPriority (DMA2_Stream7_IRQn, STANDARD_ISR_PRIORITY, 0);
  HAL_NVIC_EnableIRQ (DMA2_Stream7_IRQn);

  __HAL_LINKDMA(&huart1, hdmatx, hdma_USART_1_TX);

  HAL_NVIC_SetPriority (USART1_IRQn, STANDARD_ISR_PRIORITY, 0);
  HAL_NVIC_EnableIRQ (USART1_IRQn);

  huart1.Instance = USART1;

  huart1.Init.BaudRate = 38400; //115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init (&huart1) != HAL_OK)
    {
      ASSERT(0);
    }

  HAL_UART_Receive_IT(&huart1, &uart1_rx_byte, 1); // Activate interrupt for reception
}

void USART_1_transmit_DMA( uint8_t *pData, uint16_t Size)
{
  HAL_UART_Transmit_DMA (&huart1, pData, Size);
}

bool UART1_Receive(uint8_t *pRxByte, uint32_t timeout)
{
  BaseType_t queue_status = pdFALSE;
  if (NULL == UART1_Rx_Queue)
    {
      return false; // Return false if not initialized
    }

  queue_status = xQueueReceive(UART1_Rx_Queue, pRxByte, timeout);
  if(pdTRUE == queue_status)
    {
      return true;
    }
  else
    {
      return false;
    }
}

/**
 * @brief This function handles USART 2 global interrupt.
 */
extern "C" void USART1_IRQHandler (void)
{
  HAL_UART_IRQHandler (&huart1);
}

void UART1_RxCpltCallback(void)
{
  BaseType_t xHigherPriorityTaskWokenByPost = pdFALSE;
  BaseType_t queue_status;

  /*Get Byte and enable interrupt again*/
  queue_status = xQueueSendFromISR(UART1_Rx_Queue, &uart1_rx_byte, &xHigherPriorityTaskWokenByPost);
  HAL_UART_Receive_IT(&huart1, &uart1_rx_byte, 1);
  ASSERT(pdTRUE == queue_status);

  portYIELD_FROM_ISR(xHigherPriorityTaskWokenByPost);
}


/**
 * @brief This function handles DMA1 stream6 channel 4 global interrupt.
 */
extern "C" void DMA2_Stream7_IRQHandler (void)
{
  HAL_DMA_IRQHandler (&hdma_USART_1_TX);
#if RUN_USART_1_TEST
  BaseType_t HigherPriorityTaskWoken=0;
  vTaskNotifyGiveFromISR( USART_1_task_ID, &HigherPriorityTaskWoken);
  portEND_SWITCHING_ISR(HigherPriorityTaskWoken);
#endif
}

#if RUN_USART_1_TEST

void USART_1_runnable (void*)
{
  USART_1_task_ID = xTaskGetCurrentTaskHandle();

  acquire_privileges();
  USART_1_Init ();
  drop_privileges();

  while (true)
    {
      uint32_t pulNotificationValue;
      BaseType_t notify_result;
      volatile HAL_StatusTypeDef result;

      result = HAL_UART_Transmit_DMA (&huart1, (uint8_t *)"Hello\r\n", 7);
      //   result = HAL_UART_Transmit_IT (&huart1, (uint8_t *)"Hello\r\n", 7);
      ASSERT( result == HAL_OK);

      notify_result = xTaskNotifyWait( 0xffffffff, 0, &pulNotificationValue, INFINITE_WAIT);
      notify_result = xTaskNotifyWait( 0xffffffff, 0, &pulNotificationValue, INFINITE_WAIT);

      delay(1);
    }
}

RestrictedTask usart1_task ( USART_1_runnable, "USART1");

#endif

