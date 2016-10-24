#ifndef INTERFACE_H
#define INTERFACE_H

class Interface
{
    public:
        virtual void sync() = 0;
        virtual void startDevice() = 0;
        virtual void stopDevice() = 0;
        virtual void setDefaults() = 0;

        virtual bool empty() = 0;
        virtual void flush() = 0;
        virtual void pushInt(int) = 0;
        virtual void pushFloat(float) = 0;
        virtual void pushCommand(unsigned char) = 0;
        virtual void pushCommandImmediate(unsigned char) = 0;

        virtual int popInt() = 0;
        virtual float popFloat() = 0;
        virtual unsigned char popCommand() = 0;
};

#endif // INTERFACE_H
