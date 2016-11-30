#include "flyqueue.h"

FlyQueue::FlyQueue()
{
    reset();
}

FlyQueue::~FlyQueue()
{

}

void FlyQueue::clear()
{
    internalBuffer.clear();
}

bool FlyQueue::isEmpty()
{
    return internalBuffer.empty();
}

void FlyQueue::reset()
{
    maximumSize = 16;
    currentPacket = FlyPacket();

    internalBuffer.clear();
}

void FlyQueue::setSize(int bufferSize)
{
    maximumSize = bufferSize;
}

FlyPacket FlyQueue::pop()
{
    if (internalBuffer.empty() == false)
    {
        currentPacket = internalBuffer.front();
        internalBuffer.pop_front();
    }

    return currentPacket;
}

void FlyQueue::push(FlyPacket incomingPacket)
{
    if (internalBuffer.size() > maximumSize)
    {
        internalBuffer.pop_front();
    }

    internalBuffer.push_back(incomingPacket);
}


FlyPacket FlyQueue::operator[](const unsigned int index)
{
    return internalBuffer[index];
}
