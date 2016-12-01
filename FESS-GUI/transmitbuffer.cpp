//Custom Libraries
#include "transmitbuffer.h"

#include <QtGui>

TransmitBuffer::TransmitBuffer(){}

TransmitBuffer::~TransmitBuffer(){}

FlyByte TransmitBuffer::popByte()
{
    populateBuffer();

    FlyByte outputByte = outputByteArray.front();
    outputByteArray.pop_front();

    return outputByte;
}

void TransmitBuffer::populateBuffer()
{
    if (outputByteArray.empty() == true)
    {
        FlyPacket outputPacket = packetBuffer.pop();

        while (outputPacket.isReadable() == true)
        {
            outputByteArray.push_back(outputPacket.readByte());
        }
    }
}

void TransmitBuffer::pushByte(FlyByte incomingByte)
{
    qDebug() << "Incoming Byte: " << incomingByte;

    inputByteArray.push_back(incomingByte);

    int i = 0;
    FlyPacket inputPacket;

    if(inputByteArray.size() > inputPacket.getMaxSize())
    {
        while (inputPacket.isWriteable() == true)
        {
            inputPacket.writeByte(inputByteArray[i]);
            i++;
        }

        if (inputPacket.isValidPacket() == true)
        {
            packetBuffer.push(inputPacket);
            inputByteArray.clear();
        }

        else
        {
            inputByteArray.pop_front();
        }
    }
}

void TransmitBuffer::pushPacket(FlyPacket incomingPacket)
{
    packetBuffer.push(incomingPacket);
    populateBuffer();
}

FlyPacket TransmitBuffer::popPacket()
{
    return packetBuffer.pop();
}

bool TransmitBuffer::packetsAvailable()
{
    return !packetBuffer.isEmpty();
}

bool TransmitBuffer::bytesAvailable()
{
    return !outputByteArray.empty() | !packetBuffer.isEmpty();
}

void TransmitBuffer::flush()
{
    packetBuffer.clear();
    outputByteArray.clear();
    inputByteArray.clear();
}
