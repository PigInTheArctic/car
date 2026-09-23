/**
  ******************************************************************************
  * @file	 bsp_PWM.c
  * @author  Wang Hongxi
  * @version V1.0.0
  * @date    2020/3/1
  * @brief   
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "bsp_PWM.h"

void Car_PWM_Init(TIM_HandleTypeDef *htim,uint32_t channel,uint16_t ccr_init_value)
{
   HAL_TIM_PWM_Start(htim,channel);
   __HAL_TIM_SET_COMPARE(htim,channel,ccr_init_value);
}

void PWM_Set_CCR(TIM_HandleTypeDef *htim, uint8_t Channel, uint16_t ccr_value)
{
    __HAL_TIM_SET_COMPARE(htim,Channel,ccr_value);
}
