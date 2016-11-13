#ifndef INTERFACE_H
#define INTERFACE_H

// QT Libraries
#include <QString>

// Custom Libraries
#include "flypacket.h"

class CommonDeviceInterface
{
    public:

        CommonDeviceInterface(){}
        virtual ~CommonDeviceInterface(){}

        virtual void syncRX() = 0;
        virtual void syncTX() = 0;
        virtual bool isReady() = 0;
        virtual bool startDevice() = 0;
        virtual void stopDevice() = 0;
        virtual void setDefaults() = 0;

        virtual bool empty() = 0;
        virtual void flush() = 0;
        virtual void pushPacket(FlyPacket*) = 0;
        virtual void pushPacketImmediate(FlyPacket*) = 0;

        virtual FlyPacket* popPacket() = 0;

        virtual QString name() = 0;
};

#endif // INTERFACE_H
