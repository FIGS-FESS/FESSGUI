//Custom Libraries
#include "transmitbuffer.h"

TransmitBuffer::TransmitBuffer()
{
    outputByte = 0;
    outputPacket = nullptr;
}

TransmitBuffer::~TransmitBuffer()
{

}

FlyByte TransmitBuffer::popByte()
{
    if(outputPacket == nullptr)
    {
        outputPacket = packetBuffer.front();
        packetBuffer.pop_front();
    }
    else
    {
        if (outputPacket->isReadable() == false)
        {
            outputByte = outputPacket->readByte();
        }
        else
        {
            delete outputPacket;
            outputPacket = packetBuffer.front();
            packetBuffer.pop_front();
        }
    }

    return outputByte;
}

void TransmitBuffer::pushByte(FlyByte incomingByte)
{
    inputByteArray.push_back(incomingByte);

    if(inputByteArray.size() == PACKET_END)
    {
        FlyPacket* inputPacket = new FlyPacket;

        for (int i = 0; i < PACKET_END; i++)
        {
            inputPacket->writeByte(inputByteArray[i]);
        }

        if (inputPacket->isValid() == true)
        {
            if(packetBuffer.size() > 32)
            {
                packetBuffer.pop_front();
            }
            packetBuffer.push_back(inputPacket);
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
    if(packetBuffer.size() > 32)
    {
        packetBuffer.pop_front();
    }

    packetBuffer.push_back(&incomingPacket);
}

FlyPacket TransmitBuffer::popPacket()
{
    if(outputPacket != nullptr)
    {
        delete outputPacket;
    }

    outputPacket = packetBuffer.front();
    packetBuffer.pop_front();

    return *outputPacket;
}

bool TransmitBuffer::empty()
{
    return packetBuffer.empty();
}

void TransmitBuffer::flush()
{
    packetBuffer.clear();
}
