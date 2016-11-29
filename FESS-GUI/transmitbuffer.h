#ifndef TRANSMITBUFFER_H
#define TRANSMITBUFFER_H

// C++ Libaries
#include <deque>

// Custom Libraries
#include "flyqueue.h"
#include "flypacket.h"

class TransmitBuffer
{
    public:
        TransmitBuffer();
        ~TransmitBuffer();

        void pushByte(FlyByte);
        void pushPacket(FlyPacket);

        FlyByte popByte();
        FlyPacket popPacket();

        void flush();
        bool empty();

    private:
        FlyByte outputByte;
        FlyPacket outputPacket;

        std::deque<FlyByte> inputByteArray;
        FlyQueue packetBuffer;

};

#endif // TRANSMITBUFFER_H
