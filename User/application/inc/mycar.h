#ifndef __MYCAR_H
#define __MYCAR_H

#ifdef __cplusplus
extern "C"
{
#endif

    void Gimbal_Init();
    void Gimbal_Task();

    void Chassis_Init();
    void Chassis_Task();

    void Send_Task();
    void TotalCar_Init();
    void Decode_Task();

    void Mode_Task();

#ifdef __cplusplus
}
#endif

#endif