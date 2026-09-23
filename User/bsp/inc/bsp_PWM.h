/**
  ******************************************************************************
  * @file	 bsp_PWM.h
  * @author  Wang Hongxi
  * @version V1.0.0
  * @date    2020/3/1
  * @brief   
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __BSP_IMU_PWM_H
#define __BSP_IMU_PWM_H

#include "stdint.h"
#include "tim.h"

#ifdef __cplusplus

extern "C"{
#endif

void Car_PWM_Init(TIM_HandleTypeDef *htim,uint32_t channel,uint16_t ccr_init_value);
void PWM_Set_CCR(TIM_HandleTypeDef *htim, uint8_t Channel, uint16_t ccr_value);

#ifdef __cplusplus
}
#endif

#endif
