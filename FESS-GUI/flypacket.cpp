#include "commands.h"
#include "flypacket.h"
#include "conversions.h"

flypacket buildFlyPacket(flybyte byte)
{
    flybyte error = 0;

    flypacket decoded;

    decoded.data_type = NULL_TYPE;
    decoded.data_value = NULL_DATA;
    decoded.packet_type = NULL_PACKET;

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
                byteArrayToFloat(buffer, &decoded.data_value);
                decoded.data_type = VELOCITY;
                decoded.packet_type = DATA_PACKET;
            }

            else if (( byte == CDM_SEND_ACCELERATION ) && ( state == IDM_SEND_ACCELERATION ))
            {
                byteArrayToFloat(buffer, &decoded.data_value);
                decoded.data_type = ACCELERATION;
                decoded.packet_type = DATA_PACKET;
            }

            else if (( byte == CDM_SEND_JERK ) && ( state == IDM_SEND_JERK ))
            {
                byteArrayToFloat(buffer, &decoded.data_value);
                decoded.data_type = JERK;
                decoded.packet_type = DATA_PACKET;
            }

            else if (( byte == CDM_SEND_LOWER_DISPLACEMENT_X ) && ( state == IDM_SEND_LOWER_DISPLACEMENT_X ))
            {
                byteArrayToFloat(buffer, &decoded.data_value);
                decoded.data_type = LOWER_DISPLACMENT_X;
                decoded.packet_type = DATA_PACKET;
            }

            else if (( byte == CDM_SEND_LOWER_DISPLACEMENT_Y ) && ( state == IDM_SEND_LOWER_DISPLACEMENT_Y ))
            {
                byteArrayToFloat(buffer, &decoded.data_value);
                decoded.data_type = LOWER_DISPLACMENT_Y;
                decoded.packet_type = DATA_PACKET;
            }

            else if (( byte == CDM_SEND_UPPER_DISPLACEMENT_X ) && ( state == IDM_SEND_UPPER_DISPLACEMENT_X ))
            {
                byteArrayToFloat(buffer, &decoded.data_value);
                decoded.data_type = UPPER_DISPLACMENT_X;
                decoded.packet_type = DATA_PACKET;
            }

            else if (( byte == CDM_SEND_UPPER_DISPLACEMENT_Y ) && ( state == IDM_SEND_UPPER_DISPLACEMENT_Y ))
            {
                byteArrayToFloat(buffer, &decoded.data_value);
                decoded.data_type = UPPER_DISPLACMENT_Y;
                decoded.packet_type = DATA_PACKET;
            }

            else if (( byte == CDM_SEND_ROTATIONAL_POSITION_X) && ( state == IDM_SEND_ROTATIONAL_POSITION_X ))
            {
                byteArrayToFloat(buffer, &decoded.data_value);
                decoded.data_type = ROTATIONAL_POSITION_X;
                decoded.packet_type = DATA_PACKET;
            }

            else if (( byte == CDM_SEND_ROTATIONAL_POSITION_Y ) && ( state == IDM_SEND_ROTATIONAL_POSITION_Y ))
            {
                byteArrayToFloat(buffer, &decoded.data_value);
                decoded.data_type = ROTATIONAL_POSITION_Y;
                decoded.packet_type = DATA_PACKET;
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
