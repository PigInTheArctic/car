#include "bsp_can.h"
#include "can.h"
#include "string.h"
#include "motor.h"
#include "FreeRTOS.h"
#include "task.h"

static uint8_t rx_buffer[8];
static uint8_t rx_buffer_size = sizeof(rx_buffer);
struct rx_buff_m rx_can_buff_group[motor_num];

void TotalCar_Can_Init(CAN_HandleTypeDef *hcan)
{
    HAL_CAN_Start(hcan);
    HAL_CAN_ActivateNotification(hcan,CAN_IT_RX_FIFO0_MSG_PENDING);
    for (uint8_t i = 0;i < motor_num;i++)
    {
      rx_can_buff_group[i].rx_header = motorconfig[i].rx_header;
      rx_can_buff_group[i].hcan = motorconfig[i].hcan;
      rx_can_buff_group[i].ready_buffer = 0;
      memset(rx_can_buff_group[i].rx_buff, 0, sizeof(rx_can_buff_group[i].rx_buff));
    }
}

void Get_Can_Buff(CAN_HandleTypeDef* hcan,uint32_t _Fifo)
{
  memset(rx_buffer,0,rx_buffer_size);
  static CAN_RxHeaderTypeDef rx_header;
  HAL_CAN_GetRxMessage(hcan,_Fifo,&rx_header,rx_buffer);
    if (rx_header.DLC > rx_buffer_size)
    {
      return;
    }

    for (uint8_t i = 0; i < motor_num; i++) {
      if (rx_header.StdId == rx_can_buff_group[i].rx_header && hcan == rx_can_buff_group[i].hcan)
      {
        uint8_t next_buffer = rx_can_buff_group[i].ready_buffer ^ 1;
        memcpy(rx_can_buff_group[i].rx_buff[next_buffer], rx_buffer, rx_header.DLC);
        rx_can_buff_group[i].ready_buffer = next_buffer;
        break;
      }
    }
}

void Get_Can_Motor_Buff(uint8_t motor_index, uint8_t *rcv_buffer)
{
  if (motor_index >= motor_num)
  {
    memset(rcv_buffer, 0, 8);
    return;
  }

  taskENTER_CRITICAL();
  memcpy(rcv_buffer,
         rx_can_buff_group[motor_index].rx_buff[rx_can_buff_group[motor_index].ready_buffer],
         8);
  taskEXIT_CRITICAL();
  
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan)
{
  Get_Can_Buff(hcan, CAN_RX_FIFO0);
}

