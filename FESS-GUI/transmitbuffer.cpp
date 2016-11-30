//Custom Libraries
#include "transmitbuffer.h"

#include <QtGui>

TransmitBuffer::TransmitBuffer()
{
    outputByte = 0;
}

TransmitBuffer::~TransmitBuffer(){}

FlyByte TransmitBuffer::popByte()
{
    outputByte = packetBuffer[0].readByte();

    if (packetBuffer[0].isReadable() == false)
    {
        packetBuffer.pop();
    }

    return outputByte;
}

void TransmitBuffer::pushByte(FlyByte incomingByte)
{
    inputByteArray.push_back(incomingByte);

    if(inputByteArray.size() > PACKET_END)
    {
        FlyPacket inputPacket;

        for (int i = PACKET_BEGINNING; i < PACKET_SIZE; i++)
        {
            //qDebug() << "I: " << i << "Value:" << inputByteArray[i];
            inputPacket.writeByte(inputByteArray[i]);
        }

        if (inputPacket.isValidPacket() == true)
        {
            packetBuffer.push(inputPacket);
            inputByteArray.clear();
        }

        else
        {
            //qDebug() << inputByteArray.front();
            inputByteArray.pop_front();
        }
    }
}

void TransmitBuffer::pushPacket(FlyPacket incomingPacket)
{
    packetBuffer.push(incomingPacket);
}

FlyPacket TransmitBuffer::popPacket()
{
    outputPacket = packetBuffer.pop();

    return outputPacket;
}

bool TransmitBuffer::empty()
{
    return packetBuffer.isEmpty();
}

void TransmitBuffer::flush()
{
    packetBuffer.clear();
}
