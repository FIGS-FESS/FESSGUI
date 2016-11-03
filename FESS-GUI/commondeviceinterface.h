#ifndef INTERFACE_H
#define INTERFACE_H

#include "datatypes.h"

class CommonDeviceInterface
{
    public:
        virtual void sync() = 0;
        virtual bool ready() = 0;
        virtual void startDevice() = 0;
        virtual void stopDevice() = 0;
        virtual void setDefaults() = 0;

        virtual bool empty() = 0;
        virtual void flush() = 0;
        virtual void pushInt(int) = 0;
        virtual void pushFloat(float) = 0;
        virtual void pushCommand(flybyte) = 0;
        virtual void pushCommandImmediate(flybyte) = 0;

        virtual flybyte popCommand() = 0;
};

#endif // INTERFACE_H
