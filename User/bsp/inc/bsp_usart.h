#ifndef __BSP_USART_H
#define __BSP_USART_H

#include "usart.h"
#ifdef __cplusplus
extern "C"
{
#endif

    void TotalCar_USART_Init(UART_HandleTypeDef *huart);
    void Get_DT7_Buff(uint8_t *rcv_buffer);
    uint8_t DT7_IsConnected(void);

#ifdef __cplusplus
}
#endif

#endif