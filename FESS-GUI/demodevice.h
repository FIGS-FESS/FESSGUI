#ifndef DEMO_H
#define DEMO_H

// C++ Libraries
#include <string>

// Custom Libraries
#include "flypacket.h"
#include "transmitbuffer.h"
#include "commondeviceinterface.h"

#define RANDOM      0
#define STOP        1
#define COMMAND     2

class DemoDevice : public CommonDeviceInterface
{
    public:
        DemoDevice();
        ~DemoDevice();

        // Overriden Interface Methods
        void syncRX();
        void syncTX();
        bool isReady();
        bool startDevice();
        void stopDevice();
        void setDefaults();

        bool empty();
        void flush();
        void pushByte(FlyByte);
        void pushPacket(FlyPacket);

        FlyByte popByte();
        FlyPacket popPacket();

        QString name();


    private:
        bool broadcast;
        bool statusReady;

        float vel;
        float acc;
        float jer;
        float udx;
        float udy;
        float ldx;
        float ldy;
        float rpx;
        float rpy;

        float velRate;

        float prevVel;
        float prevAcc;
        float position;

        float key;

        int type;

        TransmitBuffer rx;
        TransmitBuffer tx;
};

#endif // DEMO_H
