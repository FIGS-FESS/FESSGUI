/*! \brief The Transmit Buffer Library, provides queueing for the communication packets and raw output of packets for interfaces.
 */

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
        bool bytesAvailable();
        bool packetsAvailable();

    private:

        void populateBuffer();

        std::deque<FlyByte> inputByteArray;
        std::deque<FlyByte> outputByteArray;
        FlyQueue packetBuffer;

};

#endif // TRANSMITBUFFER_H
