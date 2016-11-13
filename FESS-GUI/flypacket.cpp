#include "flypacket.h"
#include <QtGui>

FlyPacket::FlyPacket()
{
    errorCode = NO_ERROR;
    byteArrayPosition = PACKET_BEGINNING;
    zeroArray(byteArray);
}

FlyPacket::FlyPacket(flybyte commandByte, int dataValue)
{
    errorCode = NO_ERROR;
    byteArrayPosition = PACKET_BEGINNING;
    zeroArray(byteArray);

    setCommand(commandByte);
    setValue(dataValue);
}

FlyPacket::FlyPacket(flybyte commandByte, float dataValue)
{
    errorCode = NO_ERROR;
    byteArrayPosition = PACKET_BEGINNING;
    zeroArray(byteArray);

    //qDebug() << commandByte << " " << dataValue;

    setCommand(commandByte);
    setValue(dataValue);
}

FlyPacket::~FlyPacket(){};

bool FlyPacket::setCommand(flybyte commandByte)
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
        //qDebug() << byteArray[PACKET_BEGINNING];
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
        flybyte localbyteArray[sizeof(dataValue)];
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
        flybyte localbyteArray[sizeof(dataValue)];
        floatToByteArray(localbyteArray,&dataValue);

        for (unsigned int i = 0; i < sizeof(dataValue); i++)
        {
            byteArray[HEADER_SIZE+i] = localbyteArray[i];
        }

        //qDebug() << byteArray[0] << byteArray[1];

        return true;
    }

    else
    {
        return false;
    }
}

flybyte FlyPacket::readByte()
{
    if (byteArrayPosition < PACKET_END)
    {
        byteArrayPosition++;
    }

    return byteArray[byteArrayPosition];
}

bool FlyPacket::readingComplete()
{
    if(byteArrayPosition < PACKET_END)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// RX Command

int FlyPacket::getInt()
{
    if (checkPacket() == true)
    {
        int tempValue;
        flybyte tempBuffer[4];

        sliceArray(tempBuffer, byteArray, DATA_BEGINNING, DATA_END);
        byteArrayToInt(tempBuffer,&tempValue);

        return tempValue;
    }

    return 0;
}

float FlyPacket::getFloat()
{
    if (checkPacket() == true)
    {
        float tempValue;
        flybyte tempBuffer[4];

        sliceArray(tempBuffer, byteArray, DATA_BEGINNING, DATA_END);
        byteArrayToFloat(tempBuffer,&tempValue);

        return tempValue;
    }

    return 0.0;
}


flybyte FlyPacket::getCommand()
{
    if(byteArrayPosition > 0)
    {
        return byteArray[0];
    }

    return 0;
}

bool FlyPacket::writeByte(flybyte generalByte)
{
    if (byteArrayPosition < PACKET_SIZE)
    {
        byteArray[byteArrayPosition] = generalByte;
        byteArrayPosition++;
        return true;
    }
    else
    {
        return false;
    }
}

bool FlyPacket::writingComplete()
{
    if(byteArrayPosition < PACKET_END)
    {
        return false;
    }
    else
    {
        return true;
    }
}


// Universal Commands

void FlyPacket::resetIndex()
{
    byteArrayPosition = PACKET_BEGINNING;
}


bool FlyPacket::errorOccurred()
{
    if (errorCode != NO_ERROR)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int FlyPacket::getErrorCode()
{
    return errorCode;
}

// Private Helper Functions

bool FlyPacket::checkPacket()
{
    qDebug() << byteArray[PACKET_END] << byteArray[PACKET_BEGINNING];

    if (byteArray[PACKET_END] == (byteArray[PACKET_BEGINNING] | IDM_CMD_DIFFERENCE))
    {
        qDebug() << "T";
        return true;
    }
    else
    {
        return false;
    }
}
