#ifndef __GIMBAL_H
#define __GIMBAL_H

#include "pid.h"
class Gimbal
{
public:
    Pid speed_;

    void Pid_Init();
    void Control();
    void Remote();
    void SetYawAngle(float _yaw_angle) { yaw_target_angle = _yaw_angle; };
    void SetjiaAngle(float _jia_angle) { jia_target_angle = _jia_angle; };
    void SetSigSpeed(float _Sig_speed) { speed_target = _Sig_speed; };

    int16_t output_I_;
    float speed_rcv;
    float angle_rcv;
    float yaw_target_angle;
    float jia_target_angle;

private:
    float speed_target;
    void Pid_Clear_Control();
};

extern Gimbal gimbal;

#endif