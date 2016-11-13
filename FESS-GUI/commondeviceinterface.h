#ifndef INTERFACE_H
#define INTERFACE_H

// QT Libraries
#include <QString>

// Custom Libraries
#include "datatypes.h"

class CommonDeviceInterface
{
    public:

        CommonDeviceInterface(){}
        virtual ~CommonDeviceInterface(){}

        virtual void sync() = 0;
        virtual bool isReady() = 0;
        virtual bool startDevice() = 0;
        virtual void stopDevice() = 0;
        virtual void setDefaults() = 0;

        virtual bool empty() = 0;
        virtual void flush() = 0;
        virtual void pushInt(int) = 0;
        virtual void pushFloat(float) = 0;
        virtual void pushCommand(flybyte) = 0;
        virtual void pushCommandImmediate(flybyte) = 0;

        virtual flybyte popCommand() = 0;

        virtual QString name() = 0;
};

#endif // INTERFACE_H
