
#include <cstdint>
#include "conversionlib.h"
#include "transmitbuffer.h"

TransmitBuffer::TransmitBuffer(){}
TransmitBuffer::~TransmitBuffer(){}

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

void TransmitBuffer::pushInt(int val)
{
    uint8_t bytes[4];

    intToByteArray(bytes,&val);

    buffer.push_back(bytes[0]);
    buffer.push_back(bytes[1]);
    buffer.push_back(bytes[2]);
    buffer.push_back(bytes[3]);
}

void TransmitBuffer::pushFloat(float val)
{
    uint8_t bytes[4];

    floatToByteArray(bytes,&val);

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


