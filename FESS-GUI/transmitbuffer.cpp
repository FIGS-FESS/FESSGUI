//Custom Libraries
#include "transmitbuffer.h"

#include <QtGui>

TransmitBuffer::TransmitBuffer()
{
    outputByte = 0;
    outputPacket = nullptr;
}

TransmitBuffer::~TransmitBuffer()
{
    delete outputPacket;
}

FlyByte TransmitBuffer::popByte()
{
    if(outputPacket == nullptr)
    {
        outputPacket = packetBuffer.pop();
    }
    else
    {
        if (outputPacket->isReadable() == false)
        {
            outputByte = outputPacket->readByte();
        }
        else
        {
            outputPacket = packetBuffer.pop();
        }
    }

    return outputByte;
}

void TransmitBuffer::pushByte(FlyByte incomingByte)
{
    inputByteArray.push_back(incomingByte);

    if(inputByteArray.size() > PACKET_END)
    {
        FlyPacket* inputPacket = new FlyPacket;

        for (int i = PACKET_BEGINNING; i < DATA_BEGINNING; i++)
        {
            inputPacket->writeByte(inputByteArray[i]);
        }

        if (inputPacket->isValidCommand() == true)
        {
            for (int i = DATA_BEGINNING; i <= PACKET_END; i++)
            {
                //qDebug() << "I: " << i << "Value:" << inputByteArray[i];
                inputPacket->writeByte(inputByteArray[i]);
            }

            if (inputPacket->isValidPacket() == true)
            {
                packetBuffer.push(inputPacket);
                inputByteArray.clear();
            }

            else
            {
                //qDebug() << inputByteArray.front();
                inputByteArray.pop_front();
                delete inputPacket;
            }
        }
        else
        {
            //qDebug() << inputByteArray.front();
            inputByteArray.pop_front();
            delete inputPacket;
        }
    }
}

void TransmitBuffer::pushPacket(FlyPacket incomingPacket)
{
    packetBuffer.push(&incomingPacket);
}

FlyPacket TransmitBuffer::popPacket()
{
    outputPacket = packetBuffer.pop();

    return *outputPacket;
}

bool TransmitBuffer::empty()
{
    return packetBuffer.isEmpty();
}

void TransmitBuffer::flush()
{
    packetBuffer.clear();
    outputPacket = nullptr;
}
