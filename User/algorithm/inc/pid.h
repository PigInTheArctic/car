#ifndef __PID_H
#define __PID_H

#include "stm32f4xx.h"
#include "stdint.h"

class Pid
{
public:
    void Init(float _kp, float _ki, float _kd, float _max_output, float _dead_band);
    void Clear();
    float Calculate();
    void Limit_Output();
    void SetRef(float _ref);
    void SetMeasure(float _measure);

private:
    float kp_;
    float ki_;
    float kd_;
    float max_output_;
    float dead_band_;

    float ref_, measure_, error_;
    float ki_total_;
    float output_;
    float last_measure_, last_output_, last_error_;

    uint32_t dwt_cnt = 0;
    float dt = 0;
};

#endif
