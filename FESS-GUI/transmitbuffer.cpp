#include "transmitbuffer.h"

TransmitBuffer::TransmitBuffer(){}
TransmitBuffer::~TransmitBuffer(){}

int TransmitBuffer::popInt()
{
    unsigned char val[] = { popChar(), popChar(), popChar(),popChar() };
    return *reinterpret_cast<float*>(&val);

}

float TransmitBuffer::popFloat()
{
    unsigned char val[] = { popChar(), popChar(), popChar(),popChar() };
    return *reinterpret_cast<float*>(&val);
}

unsigned char TransmitBuffer::popChar()
{
    unsigned char val = 0;

    if(!buffer.empty())
    {
        val = buffer.front();
        buffer.pop_front();
    }
    return val;
}


void TransmitBuffer::pushChar(unsigned char byt)
{
     buffer.push_back(byt);
}

void TransmitBuffer::pushFrontChar(unsigned char byt)
{
     buffer.push_front(byt);
}

void TransmitBuffer::pushInt(int val)
{
    unsigned char *bytes = reinterpret_cast<unsigned char *>(&val);

    buffer.push_back(bytes[0]);
    buffer.push_back(bytes[1]);
    buffer.push_back(bytes[2]);
    buffer.push_back(bytes[3]);
}

void TransmitBuffer::pushFloat(float val)
{
    unsigned char *bytes = reinterpret_cast<unsigned char *>(&val);

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

