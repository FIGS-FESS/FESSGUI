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
    switch(byteArray[PACKET_BEGINNING])
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

void FlyPacket::setCommand(FlyByte commandByte)
{
    byteArray[PACKET_BEGINNING] = commandByte;
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
            byteArray[HEADER_SIZE+i] = localbyteArray[i];
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
            byteArray[HEADER_SIZE+i] = localbyteArray[i];
        }
    }
}

void FlyPacket::writeByte(FlyByte generalByte)
{
    if (writeComplete == false)
    {
        byteArray[byteArrayPosition] = generalByte;

        if (byteArrayPosition == PACKET_BEGINNING)
        {
            checkCommand();
        }

        byteArrayPosition++;

        if (byteArrayPosition > PACKET_END)
        {
            writeComplete = true;
        }
    }

}


// Getters

int FlyPacket::getInt()
{
    int tempValue;
    FlyByte tempBuffer[4];

    sliceArray(tempBuffer, byteArray, DATA_BEGINNING, DATA_END);
    byteArrayToInt(tempBuffer,&tempValue);

    return tempValue;
}

float FlyPacket::getFloat()
{
    float tempValue;
    FlyByte tempBuffer[4];

    sliceArray(tempBuffer, byteArray, DATA_BEGINNING, DATA_END);
    byteArrayToFloat(tempBuffer,&tempValue);

    return tempValue;
}

FlyByte FlyPacket::getCommand()
{
    return byteArray[0];
}

FlyByte FlyPacket::readByte()
{
    if (byteArrayPosition < PACKET_END)
    {
        byteArrayPosition++;
    }
    else
    {
        readComplete = true;
    }

    return byteArray[byteArrayPosition];
}

// Universal Commands

void FlyPacket::reset()
{
    readComplete = false;
    writeComplete = false;
    invalidCommand = false;
    byteArrayPosition = PACKET_BEGINNING;

    zeroArray(byteArray,sizeof(byteArray));
}

bool FlyPacket::isReadable()
{
    return readComplete;
}

bool FlyPacket::isWriteable()
{
    return writeComplete;
}

bool FlyPacket::isValidPacket()
{
    if (invalidCommand == false)
    {
        if (byteArray[PACKET_END] == (byteArray[PACKET_BEGINNING] | IDM_CMD_DIFFERENCE))
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
