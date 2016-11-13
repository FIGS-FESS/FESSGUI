#ifndef TRANSMITBUFFER_H
#define TRANSMITBUFFER_H

// C++ Libaries
#include <deque>

// Custom Libraries
#include "flypacket.h"

class TransmitBuffer
{
    public:
        TransmitBuffer();
        ~TransmitBuffer();

        void pushPacket(FlyPacket*);
        void pushPacketFront(FlyPacket*);

        FlyPacket* popPacket();

        void flush();
        bool empty();

    private:
        std::deque<FlyPacket*> buffer;

};

#endif // TRANSMITBUFFER_H
