#include "chassis.h"
#include "pid.h"
#include "motor.h"
#include "decode.h"
#include "user_lib.h"
#include "remote.h"

#define L 3

Chassis chassis;

void Chassis::Normal_Pid_Init()
{
    speed_[0].Init(4.0f, 0.0f, 0.3f, 3.0f, 1.0f);
    speed_[1].Init(4.0f, 0.0f, 0.3f, 3.0f, 1.0f);
    speed_[2].Init(4.0f, 0.0f, 0.3f, 3.0f, 1.0f);
    speed_[3].Init(4.0f, 0.0f, 0.3f, 3.0f, 1.0f);
}

void Chassis::Uphill_Pid_Init()
{
    speed_[0].Init(10.0f, 0.0f, 0.3f, 3.0f, 1.0f);
    speed_[1].Init(10.0f, 0.0f, 0.3f, 3.0f, 1.0f);
    speed_[2].Init(10.0f, 0.0f, 0.3f, 3.0f, 1.0f);
    speed_[3].Init(10.0f, 0.0f, 0.3f, 3.0f, 1.0f);
}

void Chassis::Control()
{
    Pid_Clear_Control();

    speed_[0].SetMeasure(speed_lf_rcv);
    speed_[1].SetMeasure(speed_rf_rcv);
    speed_[2].SetMeasure(speed_lb_rcv);
    speed_[3].SetMeasure(speed_rb_rcv);

    speed_lf = x_target_ - y_target_ - L * r_target_;
    speed_rf = x_target_ + y_target_ + L * r_target_;
    speed_lb = x_target_ + y_target_ - L * r_target_;
    speed_rb = x_target_ - y_target_ + L * r_target_;

    speed_[0].SetRef(speed_lf);
    speed_[1].SetRef(speed_rf);
    speed_[2].SetRef(speed_lb);
    speed_[3].SetRef(speed_rb);

    output_I_[0] = math::I_turn_to_sendvalue((int16_t)speed_[0].Calculate() / motorconfig[0].ratio);
    output_I_[1] = math::I_turn_to_sendvalue((int16_t)speed_[1].Calculate() / motorconfig[1].ratio);
    output_I_[2] = math::I_turn_to_sendvalue((int16_t)speed_[2].Calculate() / motorconfig[2].ratio);
    output_I_[3] = math::I_turn_to_sendvalue((int16_t)speed_[3].Calculate() / motorconfig[3].ratio);
}

void Chassis::Remote()
{
    speed_lf += math::YG_Turn_to_incre(remote.Dr16_Data.C1, 1.0f);
    speed_rf += math::YG_Turn_to_incre(remote.Dr16_Data.C2, 1.0f);
    speed_lb += math::YG_Turn_to_incre(remote.Dr16_Data.C3, 1.0f);
    speed_rb += math::YG_Turn_to_incre(remote.Dr16_Data.C3, 1.0f);

    speed_lf = math::FloatConstrain(speed_lf, -50.0f, 50.0f);
    speed_rf = math::FloatConstrain(speed_rf, -50.0f, 50.0f);
    speed_lb = math::FloatConstrain(speed_lb, -50.0f, 50.0f);
    speed_rb = math::FloatConstrain(speed_rb, -50.0f, 50.0f);
}

void Chassis::Pid_Clear_Control()
{
    if (remote.mode_change_flag == 1)
    {
        for (uint8_t i = 0; i <= 3; i++)
        {
            speed_[i].Clear();
        }

        remote.Mode_Change_Acknowledge(Remote::MODE_ACK_CHASSIS);
    }
}