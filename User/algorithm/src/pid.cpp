#include "pid.h"
#include <math.h>

#include "bsp_dwt.h"
#include "stdint.h"
#include "user_lib.h"

void Pid::Init(float _kp, float _ki, float _kd, float _max_output, float _dead_band)
{
  kp_ = _kp;
  ki_ = _ki;
  kd_ = _kd;
  max_output_ = _max_output;
  dead_band_ = _dead_band;
  Clear();
};

void Pid::Clear()
{
  ref_ = 0, error_ = 0, measure_ = 0;
  ki_total_ = 0;
  output_ = 0;
  last_measure_ = 0, last_output_ = 0, last_error_ = 0;
  dt = 0;
}

float Pid::Calculate()
{
  dt = DWT_GetDeltaT(&dwt_cnt);
  error_ = ref_ - measure_;

  if (dead_band_ < fabsf(error_))
  {
    ki_total_ += ki_ * error_ * dt;
    output_ = kp_ * error_ + ki_total_ + kd_ * (error_ - last_error_) / dt;
    Limit_Output();
  }

  else
  {
    output_ = 0.0f;
    ki_total_ = 0.0f;
  }
  last_error_ = error_;
  last_measure_ = measure_;
  last_output_ = output_;

  return output_;
}

void Pid::Limit_Output()
{
  if (output_ >= max_output_)
  {
    output_ = max_output_;
  }
  if (output_ <= -max_output_)
  {
    output_ = -max_output_;
  }
}

void Pid::SetRef(float _ref)
{
  ref_ = _ref;
}

void Pid::SetMeasure(float _measure)
{
  measure_ = _measure;
}