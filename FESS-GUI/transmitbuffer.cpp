
#include <cstdint>
#include "transmitbuffer.h"

TransmitBuffer::TransmitBuffer(){}
TransmitBuffer::~TransmitBuffer(){}

/*
int TransmitBuffer::popInt()
{
    uint8_t val[] = { popbyte(), popbyte(), popbyte(),popbyte() };
    return *reinterpret_cast<int*>(&val);

}

float TransmitBuffer::popFloat()
{
    uint8_t val[] = { popByte(), popByte(), popByte(),popByte() };
    return *reinterpret_cast<float*>(&val);
}
*/

uint8_t TransmitBuffer::popByte()
{
    uint8_t val = 0;

    if(!buffer.empty())
    {
        val = buffer.front();
        buffer.pop_front();
    }
    return val;
}

void TransmitBuffer::pushByte(uint8_t byt)
{
     buffer.push_back(byt);
}

void TransmitBuffer::pushByteFront(uint8_t byt)
{
     buffer.push_front(byt);
}

void TransmitBuffer::pushInt(int32_t val)
{
    uint8_t *bytes = reinterpret_cast<uint8_t*>(&val);

    buffer.push_back(bytes[0]);
    buffer.push_back(bytes[1]);
    buffer.push_back(bytes[2]);
    buffer.push_back(bytes[3]);
}

void TransmitBuffer::pushFloat(float val)
{
    uint8_t *bytes = reinterpret_cast<uint8_t*>(&val);

    buffer.push_back(bytes[0]);
    buffer.push_back(bytes[1]);
    buffer.push_back(bytes[2]);
    buffer.push_back(bytes[3]);
}

bool TransmitBuffer::empty()
{
    return buffer.empty();
}

void TransmitBuffer::flush()
{
    buffer.clear();
}


