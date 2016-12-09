// Custom Libraries
#include "flypacket.h"

/*! \brief FlyPacket::FlyPacket Set the default values.
 */
FlyPacket::FlyPacket()
{
    reset();
}

/*! \brief FlyPacket::FlyPacket Set the default values, header and data.
 *  \param FlyByte Header Byte
 *  \param int Data Byte
 */
FlyPacket::FlyPacket(FlyByte commandByte, int dataValue)
{
    reset();
    setCommand(commandByte);
    setValue(dataValue);
}

/*! \brief FlyPacket::FlyPacket Set the default values, header and data.
 *  \param FlyByte Header Byte
 *  \param float Data Byte
 */
FlyPacket::FlyPacket(FlyByte commandByte, float dataValue)
{
    reset();
    setCommand(commandByte);
    setValue(dataValue);
}

/*! \brief FlyPacket::~FlyPacket Empty Destructor
 */
FlyPacket::~FlyPacket(){};

// Setters

/*! \brief FlyPacket::checkCommand Checks the header to ensure it is valid.
 */
void FlyPacket::checkCommand()
{
    switch(commandByte)
    {
        case ICM_EMERGENCY_STOP:                invalidCommand = false; break;
        case ICM_SET_VELOCITY:                  invalidCommand = false; break;
        case ICM_SET_ACCELERATION:              invalidCommand = false; break;
        case ICM_SET_JERK:                      invalidCommand = false; break;
        case IDM_SEND_VELOCITY:                 invalidCommand = false; break;
        case IDM_SEND_ACCELERATION:             invalidCommand = false; break;
        case IDM_SEND_JERK:                     invalidCommand = false; break;
        case IDM_SEND_LOWER_DISPLACEMENT_X:     invalidCommand = false; break;
        case IDM_SEND_LOWER_DISPLACEMENT_Y:     invalidCommand = false; break;
        case IDM_SEND_UPPER_DISPLACEMENT_X:     invalidCommand = false; break;
        case IDM_SEND_UPPER_DISPLACEMENT_Y:     invalidCommand = false; break;
        case IDM_SEND_ROTATIONAL_POSITION_X:    invalidCommand = false; break;
        case IDM_SEND_ROTATIONAL_POSITION_Y:    invalidCommand = false; break;
        default:                                invalidCommand = true; break;
    }
}

/*! \brief FlyPacket::setCommand Sets the header of the packet and generates the footer.
 *  \param FlyByte
 */
void FlyPacket::setCommand(FlyByte generalByte)
{
    commandByte = generalByte;
    acknowledgeByte = (generalByte | IDM_CMD_DIFFERENCE);
    checkCommand();
}

/*! \brief FlyPacket:setValue Converts a int into a byte array and inserts it into the packet.
 *  \param int
 */
void FlyPacket::setValue(int dataValue)
{
    if (sizeof(dataValue) <= MAX_PAYLOAD)
    {
        FlyByte localbyteArray[sizeof(dataValue)];
        intToByteArray(localbyteArray,&dataValue);

        for (unsigned int i = 0; i < sizeof(dataValue); i++)
        {
            byteArray[i] = localbyteArray[i];
        }
    }
}

/*! \brief FlyPacket:setValue Converts a float into a byte array and inserts it into the packet.
 *  \param float
 */
void FlyPacket::setValue(float dataValue)
{
    if (sizeof(dataValue) <= MAX_PAYLOAD)
    {
        FlyByte localbyteArray[sizeof(dataValue)];
        floatToByteArray(localbyteArray,&dataValue);

        for (unsigned int i = 0; i < sizeof(dataValue); i++)
        {
            byteArray[i] = localbyteArray[i];
        }
    }
}

/*! \brief FlyPacket::writeByte Writes one byte into the packet until it is full.
 * Sequence: Header, Data, ..., Data, Footer.
 *  \param FlyByte
 */
void FlyPacket::writeByte(FlyByte generalByte)
{

    switch(byteArrayPositionWrite)
    {
        case PACKET_BEGINNING:
        {
            commandByte = generalByte;
            byteArrayPositionWrite++;
            checkCommand();
            break;
        }
        case PACKET_END:
        {
            acknowledgeByte = generalByte;
            writeComplete = true;
            break;
        }
        default:
        {
            byteArray[byteArrayPositionWrite-DATA_BEGINNING] = generalByte;
            byteArrayPositionWrite++;
            break;
        }
    }
}

// Getters

/*! \brief FlyPacket::getInt Converts the internal data bytes into a int
 * \return int
 */
int FlyPacket::getInt()
{
    return byteArrayToInt(byteArray);
}

/*! \brief FlyPacket::getFloat Converts the internal data bytes into a float
 * \return float
 */
float FlyPacket::getFloat()
{
    return byteArrayToFloat(byteArray);
}

/*! \brief FlyPacket::getCommand Get the header byte.
 * \return FlyByte
 */
FlyByte FlyPacket::getCommand()
{
    return commandByte;
}

/*! \brief FlyPacket::readByte Reads one byte from the packet and advances to the next byte.
 * \return FlyByte
 */
FlyByte FlyPacket::readByte()
{
    FlyByte returnByte;

    switch(byteArrayPositionRead)
    {
        case PACKET_BEGINNING:
        {
            returnByte = commandByte;
            byteArrayPositionRead++;
            break;
        }
        case PACKET_END:
        {
            returnByte = acknowledgeByte;
            readComplete = true;
            break;
        }
        default:
        {
            returnByte = byteArray[byteArrayPositionRead-DATA_BEGINNING];
            byteArrayPositionRead++;
            break;
        }
    }

    return returnByte;
}

// Universal Commands

/*! \brief FlyPacket::reset Resets the packet to all zeros: data,header and footer.
 */
void FlyPacket::reset()
{
    readComplete = false;
    writeComplete = false;
    invalidCommand = false;
    byteArrayPositionWrite = PACKET_BEGINNING;
    byteArrayPositionRead = PACKET_BEGINNING;

    zeroArray(byteArray,sizeof(byteArray));
}

/*!
 * \brief FlyPacket::isReadable
 * Check the packet to see if all the internal bytes have been read.
 * \return bool (true=yes, false=no)
 */
bool FlyPacket::isReadable()
{
    return !readComplete;
}

/*!
 * \brief FlyPacket::isWriteable
 * Check the packet to see if it has space for more bytes.
 * \return bool (true=yes, false=no)
 */
bool FlyPacket::isWriteable()
{
    return !writeComplete;
}

/*!
 * \brief FlyPacket::isValidPacket()
 * Check if the packet is valid.
 * \return bool (true=valid, false=invalid)
 */
bool FlyPacket::isValidPacket()
{
    if (invalidCommand == false)
    {

        if (acknowledgeByte == (commandByte | IDM_CMD_DIFFERENCE))
        {
            return true;
        }
    }

    return false;
}

/*!
 * \brief FlyPacket::isValidCommand
 * Check if the header is valid.
 * \return bool (true=valid, false=invalid)
 */
bool FlyPacket::isValidCommand()
{
    return !invalidCommand;
}

/*!
 * \brief FlyPacket::getMaxSize
 * Get the maximum packet size
 * \return int (PACKET_SIZE)
 */
FlyByte FlyPacket::getMaxSize()
{
    return PACKET_SIZE;
}
