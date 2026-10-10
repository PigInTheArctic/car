#include "bsp_usart.h"
#include "usart.h"
#include "string.h"
#include "FreeRTOS.h"
#include "task.h"

static uint8_t rx_buffer[18];
static uint8_t rx_buffer_size = sizeof(rx_buffer);
static uint8_t save_buffer[18];
static volatile uint8_t dt7_received;
static volatile uint32_t dt7_last_rx_ms;

#define DT7_TIMEOUT_MS 100

static void USART_StartReceive(UART_HandleTypeDef *huart)
{
  memset(rx_buffer, 0, rx_buffer_size);
  if (HAL_UARTEx_ReceiveToIdle_DMA(huart, rx_buffer, rx_buffer_size) != HAL_OK)
  {
    Error_Handler();
    return;
  }
  __HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);
}

void TotalCar_USART_Init(UART_HandleTypeDef *huart)
{
  dt7_received = 0;
  dt7_last_rx_ms = HAL_GetTick();
  if (huart != &huart3)
  {
    Error_Handler();
    return;
  }
  USART_StartReceive(huart);
}

void Get_DT7_Buff(uint8_t *rcv_buffer)
{
  taskENTER_CRITICAL();                     //避免save_buffer在其中被修改
   memset(rcv_buffer,0,rx_buffer_size);
   memcpy(rcv_buffer,save_buffer,rx_buffer_size);
  taskEXIT_CRITICAL();
}

uint8_t DT7_IsConnected(void)
{
  return (dt7_received != 0) &&
      ((HAL_GetTick() - dt7_last_rx_ms) <= DT7_TIMEOUT_MS);
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef* huart,uint16_t Size)
{
  if (huart == &huart3 && Size >= rx_buffer_size)
  {
    memcpy(save_buffer,rx_buffer,rx_buffer_size);
    dt7_last_rx_ms = HAL_GetTick();
    dt7_received = 1;
  }

  USART_StartReceive(huart);
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
  if (huart != &huart3)
  {
    return;
  }

  __HAL_UART_CLEAR_PEFLAG(huart); //清理错误标志，避免妨碍接收
  USART_StartReceive(huart);
}