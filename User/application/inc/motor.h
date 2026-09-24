#ifndef __MOTOR_H
#define __MOTOR_H

#include "can.h"
#include "tim.h"

#define motor_num 5
#define servo_num 2
#define M3508_RATIO 3591.0f / 187.0f

#ifdef __cplusplus
extern "C"
{
#endif

    void MotorCanSend(CAN_HandleTypeDef *_phcan, uint32_t _idx, int16_t _data1, int16_t _data2, int16_t _data3, int16_t _data4);
    void ServoSend(TIM_HandleTypeDef *htim, uint8_t Channel, float _angle);
    void TotalCar_PWM_Init();

    enum DeviceID
    {
        Wheel_LF = 0,
        Wheel_RF,
        Wheel_LB,
        Wheel_RB,
        Lead_Screw,
        Turn_Yaw,
        Jia_Zhua,
    };

    struct Motor_Config
    {
        CAN_HandleTypeDef *hcan;
        uint16_t rx_header;
        float ratio;  // 减速比
        float offset; // 补偿
        enum DeviceID dev_id;
    };

    struct Servo_Config
    {
        TIM_HandleTypeDef *htim;
        uint32_t channel;
        float init_angle;
        enum DeviceID dev_id;
    };

    const extern struct Motor_Config motorconfig[];
    const extern struct Servo_Config servoconfig[];

#ifdef __cplusplus
}
#endif

#endif