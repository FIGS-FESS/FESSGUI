#ifndef TRANSMITBUFFER_H
#define TRANSMITBUFFER_H

// C Libraries
#include <cinttypes>

// C++ Libaries
#include <deque>

class TransmitBuffer
{
    public:
        TransmitBuffer();
        ~TransmitBuffer();

        void pushInt(int32_t);
        void pushFloat(float);
        void pushByte(uint8_t);
        void pushByteFront(uint8_t);

        uint8_t popByte();

        void flush();
        bool empty();

    private:
        std::deque<uint8_t> buffer;

};

#endif // TRANSMITBUFFER_H
