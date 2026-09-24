#include "gimbal.h"
#include "motor.h"
#include "decode.h"
#include "user_lib.h"
#include "remote.h"

Gimbal gimbal;

void Gimbal::Pid_Init()
{
    speed_.Init(4.0f, 0.0f, 0.3f, 3.0f, 1.0f);
}

void Gimbal::Control()
{
    // Remote();
    Pid_Clear_Control();
    speed_.SetMeasure(speed_rcv);
    speed_.SetRef(speed_target);
    output_I_ = math::I_turn_to_sendvalue(speed_.Calculate()); // 丝杠电机控制
}

void Gimbal::Remote()
{   
    speed_target += math::YG_Turn_to_incre(remote.Dr16_Data.C1, 1.0f);
    yaw_target_angle += math::YG_Turn_to_incre(remote.Dr16_Data.C2, 1.0f);
    jia_target_angle += math::YG_Turn_to_incre(remote.Dr16_Data.C3, 1.0f);

    speed_target = math::FloatConstrain(speed_target, -100.0f, 100.0f);
    yaw_target_angle = math::FloatConstrain(yaw_target_angle, -90.0f, 90.0f);
    jia_target_angle = math::FloatConstrain(jia_target_angle, 0.0f, 45.0f);
}

void Gimbal::Pid_Clear_Control()
{
    if (remote.mode_change_flag == 1)
    {
        speed_.Clear();
        remote.Mode_Change_Acknowledge(Remote::MODE_ACK_GIMBAL);
    }
}
