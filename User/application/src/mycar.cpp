#include "mycar.h"
#include "chassis.h"
#include "gimbal.h"
#include "bsp_dwt.h"
#include "bsp_can.h"
#include "bsp_PWM.h"
#include "bsp_usart.h"
#include "usart.h"
#include "can.h"
#include "decode.h"
#include "motor.h"
#include "remote.h"

void Gimbal_Init()
{
    gimbal.Pid_Init();
}

void Gimbal_Task()
{
    gimbal.Control();
}

void Chassis_Init()
{
    chassis.Normal_Pid_Init();
}

void Chassis_Task()
{
    chassis.Control();
}

void Send_Task()
{
    if (remote.carstatus == remote.Car_Status::CAR_STOP || remote.carstatus == remote.Car_Status::CAR_REMOTE_LOSS)
    {
        MotorCanSend(&hcan1, 0x200, 0, 0, 0, 0);
        MotorCanSend(&hcan1, 0x1FF, 0, 0, 0, 0);
        ServoSend(&htim1, TIM_CHANNEL_1, 0);
        ServoSend(&htim1, TIM_CHANNEL_2, 0);
    }
    else if (remote.sig_extreme_flag)
    {
        MotorCanSend(&hcan1, 0x200, chassis.output_I_[0], chassis.output_I_[1], chassis.output_I_[2], chassis.output_I_[3]);
        MotorCanSend(&hcan1, 0x1FF, 0, 0, 0, 0);
        ServoSend(&htim1, TIM_CHANNEL_1, gimbal.yaw_target_angle);
        ServoSend(&htim1, TIM_CHANNEL_2, gimbal.jia_target_angle);
        gimbal.SetSigSpeed(0);
        remote.sig_extreme_flag = 0;
    }
    else
    {
        MotorCanSend(&hcan1, 0x200, chassis.output_I_[0], chassis.output_I_[1], chassis.output_I_[2], chassis.output_I_[3]);
        MotorCanSend(&hcan1, 0x1FF, gimbal.output_I_, 0, 0, 0);
        ServoSend(&htim1, TIM_CHANNEL_1, gimbal.yaw_target_angle);
        ServoSend(&htim1, TIM_CHANNEL_2, gimbal.jia_target_angle);
    }
}

void TotalCar_Init()
{
    TotalCar_Can_Init(&hcan1);
    TotalCar_USART_Init(&huart3);
    TotalCar_PWM_Init();
}

void Decode_Task()
{
    decode.task();
}

void Mode_Task()
{
    remote.mode_task();
}
