#include "flyqueue.h"

/*!
 * \brief FlyQueue::FlyQueue Sets the default values for the queue.
 */
FlyQueue::FlyQueue()
{
    reset();
}

/*!
 * \brief FlyQueue::~FlyQueue Empty Destructor
 */
FlyQueue::~FlyQueue(){}

/*!
 * \brief FlyQueue::clear Empties the queue.
 */
void FlyQueue::clear()
{
    internalBuffer.clear();
}

/*!
 * \brief FlyQueue::isEmpty Check if the queue is empty.
 * \return bool (True=Empty, False=Not Empty)
 */
bool FlyQueue::isEmpty()
{
    return internalBuffer.empty();
}

/*!
 * \brief FlyQueue::reset Restores the default values and empties the queue.
 */
void FlyQueue::reset()
{
    maximumSize = 16;
    currentPacket = FlyPacket();

    internalBuffer.clear();
}

/*!
 * \brief FlyQueue::setSize Sets the maximum size for the queue.
 */
void FlyQueue::setSize(int bufferSize)
{
    maximumSize = bufferSize;
}

/*!
 * \brief FlyQueue::pop Gets the first packet from the queue and removes it from the queue.
 * \return FlyPacket
 */
FlyPacket FlyQueue::pop()
{
    if (internalBuffer.empty() == false)
    {
        currentPacket = internalBuffer.front();
        internalBuffer.pop_front();
    }

    return currentPacket;
}

/*!
 * \brief FlyQueue::push Puts a packet at the end of the queue.
 */
void FlyQueue::push(FlyPacket incomingPacket)
{
    if (internalBuffer.size() > maximumSize)
    {
        internalBuffer.pop_front();
    }

    internalBuffer.push_back(incomingPacket);
}

/*!
 * \brief FlyQueue::operator[] Allows random access into the queue.
 * \param int (index in queue)
 * \return FlyPacket
 */
FlyPacket FlyQueue::operator[](const unsigned int index)
{
    return internalBuffer[index];
}
