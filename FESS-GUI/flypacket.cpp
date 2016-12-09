#include "flypacket.h"
#include <QtGui>

FlyPacket::FlyPacket()
{
    reset();
}

FlyPacket::FlyPacket(FlyByte commandByte, int dataValue)
{
    reset();
    setCommand(commandByte);
    setValue(dataValue);
}

FlyPacket::FlyPacket(FlyByte commandByte, float dataValue)
{
    reset();
    setCommand(commandByte);
    setValue(dataValue);
}

FlyPacket::~FlyPacket(){};

// Setters

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

void FlyPacket::setCommand(FlyByte generalByte)
{
    commandByte = generalByte;
    acknowledgeByte = (generalByte | IDM_CMD_DIFFERENCE);
    checkCommand();
}

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

int FlyPacket::getInt()
{
    return byteArrayToInt(byteArray);
}

float FlyPacket::getFloat()
{
    return byteArrayToFloat(byteArray);
}

FlyByte FlyPacket::getCommand()
{
    return commandByte;
}

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

void FlyPacket::reset()
{
    readComplete = false;
    writeComplete = false;
    invalidCommand = false;
    byteArrayPositionWrite = PACKET_BEGINNING;
    byteArrayPositionRead = PACKET_BEGINNING;

    zeroArray(byteArray,sizeof(byteArray));
}

bool FlyPacket::isReadable()
{
    return !readComplete;
}

bool FlyPacket::isWriteable()
{
    return !writeComplete;
}

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

bool FlyPacket::isValidCommand()
{
    return !invalidCommand;
}

FlyByte FlyPacket::getMaxSize()
{
    return PACKET_SIZE;
}
