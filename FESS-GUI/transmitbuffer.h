#ifndef TRANSMITBUFFER_H
#define TRANSMITBUFFER_H

// C++ Libaries
#include <deque>

// Custom Libraries
#include "datatypes.h"

class TransmitBuffer
{
    public:
        TransmitBuffer();
        ~TransmitBuffer();

        void pushInt(int);
        void pushFloat(float);
        void pushByte(flybyte);
        void pushByteFront(flybyte);

        flybyte popByte();

        void flush();
        bool empty();

    private:
        std::deque<flybyte> buffer;

};

#endif // TRANSMITBUFFER_H
