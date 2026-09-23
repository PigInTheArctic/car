#include "motor.h"
#include "tim.h"
#include "bsp_PWM.h"
#include "user_lib.h"

const Motor_Config motorconfig[]{
    {&hcan1, 0x206, 1.0f, 0.0f, Wheel_LF},
    {&hcan1, 0x207, 1.0f, 0.0f, Wheel_RF},
    {&hcan1, 0x208, 1.0f, 0.0f, Wheel_LB},
    {&hcan1, 0x209, 1.0f, 0.0f, Wheel_RB},
    {&hcan1, 0x210, 1.0f, 0.0f, Lead_Screw},
};

const Servo_Config servoconfig[]{
    {&htim1, TIM_CHANNEL_1, 0.0f, Turn_Yaw},
    {&htim1, TIM_CHANNEL_2, 0.0f, Jia_Zhua},
};

void MotorCanSend(CAN_HandleTypeDef *_phcan, uint32_t _idx, int16_t _data1, int16_t _data2, int16_t _data3, int16_t _data4)
{
    CAN_TxHeaderTypeDef tx_conf = {0};
    uint8_t tx_data[8];
    uint32_t tx_mailbox;

    tx_conf.StdId = _idx;
    tx_conf.IDE = CAN_ID_STD;
    tx_conf.RTR = CAN_RTR_DATA;
    tx_conf.DLC = 8;

    tx_data[0] = _data1 >> 8;
    tx_data[1] = _data1;
    tx_data[2] = _data2 >> 8;
    tx_data[3] = _data2;
    tx_data[4] = _data3 >> 8;
    tx_data[5] = _data3;
    tx_data[6] = _data4 >> 8;
    tx_data[7] = _data4;

    if (HAL_CAN_AddTxMessage(_phcan, &tx_conf, tx_data, &tx_mailbox) != HAL_OK)
    {
        return;
    }
}

void ServoSend(TIM_HandleTypeDef *htim, uint8_t Channel, float _angle)
{
    uint16_t ccr_value = math::angle_turn_to_ccr(_angle);
    for (uint8_t i = 0; i < servo_num; i++)
    {
        if (htim == servoconfig[i].htim && Channel == servoconfig[i].channel)
        {
            PWM_Set_CCR(htim, Channel, ccr_value);
        }
    }
}

void TotalCar_PWM_Init()
{
    for (uint8_t i = 0; i < servo_num; i++)
    {
        Car_PWM_Init(servoconfig[i].htim, servoconfig[i].channel, math::angle_turn_to_ccr(servoconfig[i].init_angle));
    }
}