#ifndef DEMO_H
#define DEMO_H

// Custom Libraries
#include "interface.h"

#define RANDOM      0
#define STOP        1
#define COMMAND     2

class Demo : public Interface
{
    public:
        Demo();

        void sync();

    private:
        bool broadcast;

        float vel;
        float acc;
        float jer;
        float udx;
        float udy;
        float ldx;
        float ldy;
        float rpx;
        float rpy;

        float ve_rate;

        float prev_vel;
        float prev_acc;
        float position;

        float key;

        int type;
};

#endif // DEMO_H
