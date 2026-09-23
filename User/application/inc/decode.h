#ifndef __DT16_H
#define __DT16_H

#include "stdint.h"

#ifdef __cplusplus
extern "C"
{
#endif

    class Decode
    {
    public:
        void task();

    private:
        uint8_t rcv_dr16_buffer[18];
        uint8_t rcv_dr16_buffer_size = sizeof(rcv_dr16_buffer);

        void dr16_decode(void);
        void can_decode(void);
    };

    extern Decode decode;

#ifdef __cplusplus
}
#endif

#endif