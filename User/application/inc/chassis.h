#ifndef __CHASSIS_H
#define __CHASSIS_H

#include "pid.h"

class Chassis
{
public:
    Pid speed_[4];

    void Normal_Pid_Init();
    void Uphill_Pid_Init();

    void Control();
    void SetYawSpeed(float _r_target_) { r_target_ = _r_target_; };
    void SetXSpeed(float _xspd) { x_target_ = _xspd; };
    void SetYSpeed(float _yspd) { y_target_ = _yspd; };
    void Remote();

    int16_t output_I_[4];
    float speed_lf_rcv, speed_rf_rcv, speed_lb_rcv, speed_rb_rcv;
    float angle_lf_rcv, angle_rf_rcv, angle_lb_rcv, angle_rb_rcv;

private:
    float r_target_, x_target_, y_target_;
    float speed_lf, speed_rf, speed_lb, speed_rb;
    float angle_lf, angle_rf, angle_lb, angle_rb;
    void Pid_Clear_Control();
};

extern Chassis chassis;

#endif