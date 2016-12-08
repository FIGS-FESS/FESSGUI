//Custom Libraries
#include "transmitbuffer.h"

/*! \brief TransmitBuffer::TransmitBuffer Provided if needed in the future, currently no functionality.
 */
TransmitBuffer::TransmitBuffer(){}

/*! \brief TransmitBuffer::~TransmitBuffer Provided if needed in the future, currently no functionality.
 */
TransmitBuffer::~TransmitBuffer(){}

/*! \brief TransmitBuffer::popByte Get the Byte at the front of the output byte queue created from a packet.
 *  \return FlyByte
 */
FlyByte TransmitBuffer::popByte()
{
    populateBuffer();

    FlyByte outputByte = outputByteArray.front();
    outputByteArray.pop_front();

    return outputByte;
}

/*! \brief TransmitBuffer::populateBuffer When the ouput byte queue is empty it grabs a packet from the packet queue and adds its data to the output byte queue.
 */
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

/*! \brief TransmitBuffer::pushByte Takes bytes until there are enough to build a packet. It converts the bytes to a packet and adds the packet to the packet queue.
 *  \param FlyByte
 */
void TransmitBuffer::pushByte(FlyByte incomingByte)
{
    inputByteArray.push_back(incomingByte);

    FlyPacket inputPacket;

    if(inputByteArray.size() == inputPacket.getMaxSize())
    {
        for(int i=0; i < inputPacket.getMaxSize(); i++)
        {
            inputPacket.writeByte(inputByteArray[i]);
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

/*! \brief TransmitBuffer::pushPacket Adds the packets to the packet queue.
 *  \param FlyPacket
 */
void TransmitBuffer::pushPacket(FlyPacket incomingPacket)
{
    packetBuffer.push(incomingPacket);
    populateBuffer();
}

/*! \brief TransmitBuffer::popPacket Adds the packets to the packet queue.
 *  \return FlyPacket
 */
FlyPacket TransmitBuffer::popPacket()
{
    return packetBuffer.pop();
}

/*! \brief TransmitBuffer::packetsAvailable Checks if the packet queue is empty.
 *  \return True | False
 */
bool TransmitBuffer::packetsAvailable()
{
    return !packetBuffer.isEmpty();
}

/*! \brief TransmitBuffer::bytesAvailable Checks if the byte and packet queues are empty.
 *  \return True | False
 */
bool TransmitBuffer::bytesAvailable()
{
    return !outputByteArray.empty() | !packetBuffer.isEmpty();
}

/*! \brief TransmitBuffer::flush Empties all internal queues.
 */
void TransmitBuffer::flush()
{
    packetBuffer.clear();
    outputByteArray.clear();
    inputByteArray.clear();
}
