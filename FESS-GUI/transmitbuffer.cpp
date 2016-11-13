#include "transmitbuffer.h"
#include <QtGui>

TransmitBuffer::TransmitBuffer(){}
TransmitBuffer::~TransmitBuffer(){}

FlyPacket* TransmitBuffer::popPacket()
{
    FlyPacket* packet = buffer.front();
    buffer.pop_front();
    return packet;
}

void TransmitBuffer::pushPacketFront(FlyPacket *packet)
{
     buffer.push_front(packet);
}

void TransmitBuffer::pushPacket(FlyPacket *packet)
{
    //qDebug() << packet->getFloat();

    buffer.push_back(packet);
}

bool TransmitBuffer::empty()
{
    return buffer.empty();
}

void TransmitBuffer::flush()
{
    buffer.clear();
}


