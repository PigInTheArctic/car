#ifndef __BSP_CAN_H
#define __BSP_CAN_H

#include "can.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void TotalCar_Can_Init(CAN_HandleTypeDef *hcan);
    void Get_Can_Buff(CAN_HandleTypeDef *hcan, uint32_t _Fifo);
    void Get_Can_Motor_Buff(uint8_t motor_index, uint8_t *rcv_buffer);
    uint8_t Can_IsConnected();

    struct rx_buff_m
    {
        CAN_HandleTypeDef *hcan;
        uint16_t rx_header;
        uint8_t rx_buff[2][8];
        volatile uint8_t ready_buffer;
    };

    extern struct rx_buff_m rx_can_buff_group[5];

#ifdef __cplusplus
}
#endif

#endif