#include "commands.h"
#include "flypacket.h"
#include "conversions.h"

flypacket buildFlyPacket(flybyte byte)
{
    flybyte error = 0;

    flypacket decoded;

    decoded.dataType = NULL_TYPE;
    decoded.dataValue = NULL_DATA;
    decoded.packetType = NULL_PACKET;

    static flybyte buffer[4];

    static flybyte data = 0;
    static flybyte state = 0;
    static flybyte count = 0;

    if (data)
    {
        if (count == 4)
        {
            if (( byte == CDM_SEND_VELOCITY ) && ( state == IDM_SEND_VELOCITY ))
            {
                byteArrayToFloat(buffer, &decoded.dataValue);
                decoded.dataType = VELOCITY;
                decoded.packetType = DATA_PACKET;
            }

            else if (( byte == CDM_SEND_ACCELERATION ) && ( state == IDM_SEND_ACCELERATION ))
            {
                byteArrayToFloat(buffer, &decoded.dataValue);
                decoded.dataType = ACCELERATION;
                decoded.packetType = DATA_PACKET;
            }

            else if (( byte == CDM_SEND_JERK ) && ( state == IDM_SEND_JERK ))
            {
                byteArrayToFloat(buffer, &decoded.dataValue);
                decoded.dataType = JERK;
                decoded.packetType = DATA_PACKET;
            }

            else if (( byte == CDM_SEND_LOWER_DISPLACEMENT_X ) && ( state == IDM_SEND_LOWER_DISPLACEMENT_X ))
            {
                byteArrayToFloat(buffer, &decoded.dataValue);
                decoded.dataType = LOWER_DISPLACMENT_X;
                decoded.packetType = DATA_PACKET;
            }

            else if (( byte == CDM_SEND_LOWER_DISPLACEMENT_Y ) && ( state == IDM_SEND_LOWER_DISPLACEMENT_Y ))
            {
                byteArrayToFloat(buffer, &decoded.dataValue);
                decoded.dataType = LOWER_DISPLACMENT_Y;
                decoded.packetType = DATA_PACKET;
            }

            else if (( byte == CDM_SEND_UPPER_DISPLACEMENT_X ) && ( state == IDM_SEND_UPPER_DISPLACEMENT_X ))
            {
                byteArrayToFloat(buffer, &decoded.dataValue);
                decoded.dataType = UPPER_DISPLACMENT_X;
                decoded.packetType = DATA_PACKET;
            }

            else if (( byte == CDM_SEND_UPPER_DISPLACEMENT_Y ) && ( state == IDM_SEND_UPPER_DISPLACEMENT_Y ))
            {
                byteArrayToFloat(buffer, &decoded.dataValue);
                decoded.dataType = UPPER_DISPLACMENT_Y;
                decoded.packetType = DATA_PACKET;
            }

            else if (( byte == CDM_SEND_ROTATIONAL_POSITION_X) && ( state == IDM_SEND_ROTATIONAL_POSITION_X ))
            {
                byteArrayToFloat(buffer, &decoded.dataValue);
                decoded.dataType = ROTATIONAL_POSITION_X;
                decoded.packetType = DATA_PACKET;
            }

            else if (( byte == CDM_SEND_ROTATIONAL_POSITION_Y ) && ( state == IDM_SEND_ROTATIONAL_POSITION_Y ))
            {
                byteArrayToFloat(buffer, &decoded.dataValue);
                decoded.dataType = ROTATIONAL_POSITION_Y;
                decoded.packetType = DATA_PACKET;
            }

            else
            {
                error = 1;
            }

            count = 0;
            data = 0;
            state = 0;
        }

        else
        {
            buffer[count] = byte;
            count++;
        }
    }
    else
    {
        if (byte == IDM_SEND_VELOCITY)
        {
            state = IDM_SEND_VELOCITY;
            count = 0;
            data = 1;
        }

        else if (byte == IDM_SEND_ACCELERATION)
        {
            state = byte;
            count = 0;
            data = 1;
        }

        else if (byte == IDM_SEND_JERK)
        {
            state = byte;
            count = 0;
            data = 1;
        }

        else if (byte == IDM_SEND_LOWER_DISPLACEMENT_X)
        {
            state = byte;
            count = 0;
            data = 1;
        }

        else if (byte == IDM_SEND_LOWER_DISPLACEMENT_Y)
        {
            state = byte;
            count = 0;
            data = 1;
        }

        else if (byte == IDM_SEND_UPPER_DISPLACEMENT_X)
        {
            state = byte;
            count = 0;
            data = 1;
        }

        else if (byte == IDM_SEND_UPPER_DISPLACEMENT_Y)
        {
            state = byte;
            count = 0;
            data = 1;
        }

        else if (byte == IDM_SEND_ROTATIONAL_POSITION_X)
        {
            state = byte;
            count = 0;
            data = 1;
        }

        else if (byte == IDM_SEND_ROTATIONAL_POSITION_Y)
        {
            state = byte;
            count = 0;
            data = 1;
        }

        else // Error: Unknown Commands
        {
            error = 0;
        }
    }

    if (error)
    {
        //communicationDevice->flush();
        state = 0;
        count = 0;
        data = 0;
    }

    return decoded;
}
