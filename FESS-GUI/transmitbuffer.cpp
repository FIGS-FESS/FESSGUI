//Custom Libraries
#include "conversions.h"
#include "transmitbuffer.h"

TransmitBuffer::TransmitBuffer(){}
TransmitBuffer::~TransmitBuffer(){}

flybyte TransmitBuffer::popByte()
{
    flybyte val = 0;

    if(!buffer.empty())
    {
        val = buffer.front();
        buffer.pop_front();
    }
    return val;
}

void TransmitBuffer::pushByte(flybyte byt)
{
     buffer.push_back(byt);
}

void TransmitBuffer::pushByteFront(flybyte byt)
{
     buffer.push_front(byt);
}

void TransmitBuffer::pushInt(int val)
{
    flybyte bytes[4];

    intToByteArray(bytes,&val);

    buffer.push_back(bytes[0]);
    buffer.push_back(bytes[1]);
    buffer.push_back(bytes[2]);
    buffer.push_back(bytes[3]);
}

void TransmitBuffer::pushFloat(float val)
{
    flybyte bytes[4];

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


