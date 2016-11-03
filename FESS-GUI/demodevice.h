#ifndef DEMO_H
#define DEMO_H

// Custom Libraries
#include "transmitbuffer.h"
#include "commondeviceinterface.h"

#define RANDOM      0
#define STOP        1
#define COMMAND     2

class DemoDevice : public CommonDeviceInterface
{
    public:
        DemoDevice();

        // Overriden Interface Methods
        void sync();
        bool ready();
        void startDevice();
        void stopDevice();
        void setDefaults();

        bool empty();
        void flush();
        void pushInt(int);
        void pushFloat(float);
        void pushCommand(unsigned char);
        void pushCommandImmediate(unsigned char);

        int popInt();
        float popFloat();
        unsigned char popCommand();


    private:
        bool broadcast;
        bool status_ready;

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

        TransmitBuffer rx;
        TransmitBuffer tx;
};

#endif // DEMO_H
