#include "remote.h"
#include "decode.h"
#include "gimbal.h"
#include "chassis.h"
#include "bsp_usart.h"
#include "stdint.h"
#include "math.h"

Remote remote;

void Remote::mode_task()
{
    judge_status();

    switch (carstatus)
    {
    case CAR_STOP:
        gimbal.SetjiaAngle(0);
        gimbal.SetYawAngle(0);
        gimbal.SetSigSpeed(0);
        chassis.SetXSpeed(0);
        chassis.SetYawSpeed(0);
        chassis.SetYSpeed(0);
        break;
    case CAR_NORMAL:
        if (lastcarstatus != CAR_NORMAL)
        {
            chassis.Normal_Pid_Init();
        }
        chassis.Remote();
        gimbal.Remote();
        break;
    case CAR_UPHILL:
        if (lastcarstatus != CAR_UPHILL)
        {
            chassis.Uphill_Pid_Init();
        }
        chassis.Remote();
        gimbal.Remote();
        break;
    case CAR_REMOTE_LOSS:
        gimbal.SetjiaAngle(0);
        gimbal.SetYawAngle(0);
        gimbal.SetSigSpeed(0);
        chassis.SetXSpeed(0);
        chassis.SetYawSpeed(0);
        chassis.SetYSpeed(0);
        break;
    case None:
        break;
    }
}

void Remote::judge_status()
{

    Sig_Extreme_Judge();

    if (DT7_IsConnected() == 0)
    {
        carstatus = CAR_REMOTE_LOSS; // 判断是否与DT7失联
    }
    else if (Dr16_Data.S1 == 1)
    {
        carstatus = CAR_STOP;
    }
    else if (Dr16_Data.S1 == 2)
    {
        if (Dr16_Data.S2 == 2)
        {
            carstatus = CAR_NORMAL;
        }
        else if (Dr16_Data.S2 == 3)
        {
            carstatus = CAR_UPHILL;
        }
    }

    Mode_Change_Judge();

    lastcarstatus = carstatus;
}

void Remote::Mode_Change_Judge()
{

    if (lastcarstatus != carstatus)
    {
        mode_change_flag = 1;
        mode_change_ack = 0;
    }
}

void Remote::Mode_Change_Acknowledge(uint8_t ack)
{

    if (mode_change_flag == 1)
    {
        mode_change_ack |= ack;

        if (mode_change_ack == (MODE_ACK_CHASSIS | MODE_ACK_GIMBAL)) // 模式转换后的清零标志位操作
        {
            mode_change_flag = 0;
            mode_change_ack = 0;
        }
    }
}

void Remote::Sig_Extreme_Judge()
{
    if (fabsf(gimbal.output_I_) >= sig_extreme_I)
    {
        sig_extreme_count++;
    }
    else
    {
        sig_extreme_count = 0; // 判断是否到达限位处
    }

    if (sig_extreme_count >= 100)
    {
        sig_extreme_flag = 1;
        sig_extreme_count = 0;
    }
}
