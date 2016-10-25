#ifndef INTERFACE_H
#define INTERFACE_H

#include <cinttypes>

class CommonDeviceInterface
{
    public:
        virtual void sync() = 0;
        virtual void startDevice() = 0;
        virtual void stopDevice() = 0;
        virtual void setDefaults() = 0;

        virtual bool empty() = 0;
        virtual void flush() = 0;
        virtual void pushInt(int32_t) = 0;
        virtual void pushFloat(float) = 0;
        virtual void pushCommand(uint8_t) = 0;
        virtual void pushCommandImmediate(uint8_t) = 0;

        virtual uint8_t popCommand() = 0;
};

#endif // INTERFACE_H
