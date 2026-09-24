/**
 *******************************************************************************
 * @file      : user_lib.h
 * @brief     :
 * @history   :
 *  Version     Date            Author          Note
 *  V0.9.0      yyyy-mm-dd      <author>        1. <note>
 *******************************************************************************
 * @attention :
 *******************************************************************************
 *  Copyright (c) 2023 Reborn Team, USTB.
 *  All Rights Reserved.
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USER_LIB_H_
#define __USER_LIB_H_

#ifdef __cplusplus

/* Includes ------------------------------------------------------------------*/
#include <stm32f407xx.h>

#include "arm_math.h"
#include "stdint.h"
/* Exported macro ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define RAD_2_DEGREE 57.2957795f    // 180/pi
#define DEGREE_2_RAD 0.01745329252f // pi/180

/* Exported types ------------------------------------------------------------*/
namespace math
{
    float AbsLimit(float _num, float _limit);
    float Sign(float _value);
    float FloatDeadband(float _value, float _min_value, float _max_value);
    float FloatConstrain(float _value, float _min_value, float _max_value);
    int16_t Int16Constrain(int16_t _value, int16_t _min_value, int16_t _max_value);
    float LoopFloatConstrain(float _value, float _min_value, float _max_value);
    float ThetaFormat(float _ang);
    int FloatRounding(float _raw);

    uint16_t angle_turn_to_ccr(float _angle);
    float YG_Turn_to_incre(float _dr16_data, float _max_pace);
    float turn_to_real_speed(float _rcv_speed);
    float turn_to_real_angle(float _rcv_angle);
    float I_turn_to_sendvalue(float _real_speed);
    float torque_turn_to_sendvalue(float torque);
     
}; // namespace math
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/

#endif

#endif /* __USER_LIB_H_ */
