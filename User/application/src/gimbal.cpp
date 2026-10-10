#include "gimbal.h"
#include "motor.h"
#include "decode.h"
#include "user_lib.h"
#include "remote.h"

Gimbal gimbal;

void Gimbal::Pid_Init()
{
    speed_.Init(35.0f, 0.0f, 0.3f, math::I_turn_to_sendvalue(15.0f), 1.0f);
}

void Gimbal::Control()
{
    Pid_Clear_Control();
    speed_.SetMeasure(speed_rcv);
    speed_.SetRef(speed_target);
    if (remote.sig_extreme_flag)
    {
        output_I_ = 0;
    }
    else
    {
        output_I_ = speed_.Calculate(); // 丝杠电机控制
    }
}

void Gimbal::Remote()
{
    if (remote.carstatus == Remote::CAR_GIMBAL_WORK)
    {
        yaw_target_angle += math::YG_Turn_to_incre(remote.Dr16_Data.C0, 0.1f);
        jia_target_angle += math::YG_Turn_to_incre(remote.Dr16_Data.C1, 1.0f);
        speed_target = 0;
    }
    else
    {
        speed_target = math::YG_Turn_to_speed(remote.Dr16_Data.C1, 50.0f);
    }
    yaw_target_angle = math::FloatConstrain(yaw_target_angle, -90.0f, 90.0f);
    jia_target_angle = math::FloatConstrain(jia_target_angle, 0.0f, 67.0f);
}

void Gimbal::Pid_Clear_Control()
{
    if (remote.mode_change_flag == 1)
    {
        speed_.Clear();
        output_I_ = 0;
        remote.Mode_Change_Acknowledge(Remote::MODE_ACK_GIMBAL);
    }
}
