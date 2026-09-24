#include "decode.h"
#include "bsp_usart.h"
#include "bsp_can.h"
#include "stdint.h"
#include "string.h"
#include "motor.h"
#include "gimbal.h"
#include "chassis.h"
#include "remote.h"
#include "user_lib.h"

Decode decode;

void Decode::dr16_decode(void)
{
   remote.Dr16_Data.C0 = rcv_dr16_buffer[0] | (rcv_dr16_buffer[1] & 0x07) << 8;
   remote.Dr16_Data.C1 = (rcv_dr16_buffer[1] >> 3) | (rcv_dr16_buffer[2] & 0x3F) << 5;
   remote.Dr16_Data.C2 = (rcv_dr16_buffer[2] >> 6) | (rcv_dr16_buffer[3] << 2) | (rcv_dr16_buffer[4] & 0x01) << 10;
   remote.Dr16_Data.C3 = (rcv_dr16_buffer[4] >> 1) | (rcv_dr16_buffer[5] & 0x0F) << 7;
   remote.Dr16_Data.S1 = (rcv_dr16_buffer[5] >> 4) & 0x03;
   remote.Dr16_Data.S2 = (rcv_dr16_buffer[5] >> 6) & 0x03;
   remote.Dr16_Data.Bo = rcv_dr16_buffer[16] | rcv_dr16_buffer[17] << 8;
}

void Decode::can_decode(void)
{
   uint8_t rx_buff[8];

   for (uint8_t i = 0; i < motor_num; i++)
   {
      Get_Can_Motor_Buff(i, rx_buff);

      switch (i)
      {
      case 0:
         chassis.angle_lf_rcv = math::turn_to_real_angle((int16_t)(((uint16_t)rx_buff[0]) << 8 | rx_buff[1]));
         chassis.speed_lf_rcv = math::turn_to_real_speed((int16_t)(((uint16_t)rx_buff[2]) << 8 | rx_buff[3])) / motorconfig[0].ratio;
         break;
      case 1:
         chassis.angle_rf_rcv = math::turn_to_real_angle((int16_t)(((uint16_t)rx_buff[0]) << 8 | rx_buff[1]));
         chassis.speed_rf_rcv = math::turn_to_real_speed((int16_t)(((uint16_t)rx_buff[2]) << 8 | rx_buff[3])) / motorconfig[1].ratio;
         break;
      case 2:
         chassis.angle_lb_rcv = math::turn_to_real_angle((int16_t)(((uint16_t)rx_buff[0]) << 8 | rx_buff[1]));
         chassis.speed_lb_rcv = math::turn_to_real_speed((int16_t)(((uint16_t)rx_buff[2]) << 8 | rx_buff[3])) / motorconfig[2].ratio;
         break;
      case 3:
         chassis.angle_rb_rcv = math::turn_to_real_angle((int16_t)(((uint16_t)rx_buff[0]) << 8 | rx_buff[1]));
         chassis.speed_rb_rcv = math::turn_to_real_speed((int16_t)(((uint16_t)rx_buff[2]) << 8 | rx_buff[3])) / motorconfig[3].ratio;
         break;
      case 4:
         gimbal.angle_rcv = math::turn_to_real_angle((int16_t)(((uint16_t)rx_buff[0]) << 8 | rx_buff[1]));
         gimbal.speed_rcv = math::turn_to_real_speed((int16_t)(((uint16_t)rx_buff[2]) << 8 | rx_buff[3])) / motorconfig[4].ratio;
         break;
      }
   }
}

void Decode::task()
{
   Get_DT7_Buff(rcv_dr16_buffer);
   dr16_decode();
   can_decode();
}
