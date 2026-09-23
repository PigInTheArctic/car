#ifndef __REMOTE_H
#define __REMOTE_H

#define sig_extreme_I 10.0f

#include "stdint.h"

class Remote
{
public:
    void mode_task();
    void Mode_Change_Acknowledge(uint8_t ack);

    enum Mode_Change_Ack
    {
        MODE_ACK_CHASSIS = 0x01,
        MODE_ACK_GIMBAL = 0x02,
    };

    enum Car_Status
    {
        None,
        CAR_STOP,
        CAR_NORMAL,
        CAR_UPHILL,
        CAR_REMOTE_LOSS,
    };

    volatile Car_Status carstatus = Car_Status::CAR_STOP;
    Car_Status lastcarstatus = Car_Status::None;

    struct Dr16
    {
        float C0;
        float C1;
        float C2;
        float C3;
        float S1;
        float S2;
        float Bo;
    };
    struct Dr16 Dr16_Data;

    volatile uint8_t mode_change_flag = 0;
    volatile uint8_t sig_extreme_flag = 0;

private:
    uint8_t mode_change_ack = 0;
    uint16_t sig_extreme_count = 0;
    void judge_status();
    void Mode_Change_Judge();
    void Sig_Extreme_Judge();
};

extern Remote remote;

#endif