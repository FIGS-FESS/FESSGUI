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

bool FlyPacket::setCommand(FlyByte commandByte)
{
    bool commandError;
    byteArray[PACKET_BEGINNING] = commandByte;

    switch(commandByte)
    {
        case ICM_EMERGENCY_STOP:                commandError = false; break;
        case ICM_SET_VELOCITY:                  commandError = false; break;
        case ICM_SET_ACCELERATION:              commandError = false; break;
        case ICM_SET_JERK:                      commandError = false; break;
        case IDM_SEND_VELOCITY:                 commandError = false; break;
        case IDM_SEND_ACCELERATION:             commandError = false; break;
        case IDM_SEND_JERK:                     commandError = false; break;
        case IDM_SEND_LOWER_DISPLACEMENT_X:     commandError = false; break;
        case IDM_SEND_LOWER_DISPLACEMENT_Y:     commandError = false; break;
        case IDM_SEND_UPPER_DISPLACEMENT_X:     commandError = false; break;
        case IDM_SEND_UPPER_DISPLACEMENT_Y:     commandError = false; break;
        case IDM_SEND_ROTATIONAL_POSITION_X:    commandError = false; break;
        case IDM_SEND_ROTATIONAL_POSITION_Y:    commandError = false; break;
        default:                                commandError = true;  break;
    }

    if (commandError == false)
    {
        byteArray[PACKET_END] = commandByte | IDM_CMD_DIFFERENCE;
        return true;
    }
    else
    {
       return false;
    }

}

bool FlyPacket::setValue(int dataValue)
{
    if (sizeof(dataValue) <= MAX_PAYLOAD)
    {
        FlyByte localbyteArray[sizeof(dataValue)];
        intToByteArray(localbyteArray,&dataValue);

        for (unsigned int i = 0; i < sizeof(dataValue); i++)
        {
            byteArray[HEADER_SIZE+i] = localbyteArray[i];
        }

        return true;
    }

    else
    {
        return false;
    }
}

bool FlyPacket::setValue(float dataValue)
{
    if (sizeof(dataValue) <= MAX_PAYLOAD)
    {
        FlyByte localbyteArray[sizeof(dataValue)];
        floatToByteArray(localbyteArray,&dataValue);

        for (unsigned int i = 0; i < sizeof(dataValue); i++)
        {
            byteArray[HEADER_SIZE+i] = localbyteArray[i];
        }

        return true;
    }

    else
    {
        return false;
    }
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

bool FlyPacket::isReadable()
{
    return readComplete;
}

// RX Command

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

void FlyPacket::writeByte(FlyByte generalByte)
{
    if(byteArrayPosition == PACKET_BEGINNING)
    {
        setCommand(generalByte);
        byteArrayPosition++;
    }
    else
    {
        if (writeComplete == false)
        {
            byteArray[byteArrayPosition] = generalByte;
            byteArrayPosition++;

            if (byteArrayPosition > PACKET_END)
            {
                writeComplete = true;
            }
        }
    }
}

bool FlyPacket::isWriteable()
{
    return writeComplete;
}


// Universal Commands

void FlyPacket::reset()
{
    readComplete = false;
    writeComplete = false;
    byteArrayPosition = PACKET_BEGINNING;

    zeroArray(byteArray);
}

bool FlyPacket::isValid()
{
    if (byteArray[PACKET_END] == (byteArray[PACKET_BEGINNING] | IDM_CMD_DIFFERENCE))
    {
        return true;
    }
    else
    {
        return false;
    }
}
