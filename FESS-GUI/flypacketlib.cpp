#include "commands.h"
#include "flypacketlib.h"
#include "conversionlib.h"

flypacket buildFlyPacket(flybyte byte)
{
    flybyte error = 0;

    flypacket decoded;

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
                byteArrayToFloat(buffer, &decoded.value);
                decoded.type = VELOCITY;
            }

            else if (( byte == CDM_SEND_ACCELERATION ) && ( state == IDM_SEND_ACCELERATION ))
            {
                byteArrayToFloat(buffer, &decoded.value);
                decoded.type = ACCELERATION;
            }

            else if (( byte == CDM_SEND_JERK ) && ( state == IDM_SEND_JERK ))
            {
                byteArrayToFloat(buffer, &decoded.value);
                decoded.type = JERK;
            }

            else if (( byte == CDM_SEND_LOWER_DISPLACEMENT_X ) && ( state == IDM_SEND_LOWER_DISPLACEMENT_X ))
            {
                byteArrayToFloat(buffer, &decoded.value);
                decoded.type = LOWER_DISPLACMENT_X;
            }

            else if (( byte == CDM_SEND_LOWER_DISPLACEMENT_Y ) && ( state == IDM_SEND_LOWER_DISPLACEMENT_Y ))
            {
                byteArrayToFloat(buffer, &decoded.value);
                decoded.type = LOWER_DISPLACMENT_Y;
            }

            else if (( byte == CDM_SEND_UPPER_DISPLACEMENT_X ) && ( state == IDM_SEND_UPPER_DISPLACEMENT_X ))
            {
                byteArrayToFloat(buffer, &decoded.value);
                decoded.type = UPPER_DISPLACMENT_X;
            }

            else if (( byte == CDM_SEND_UPPER_DISPLACEMENT_Y ) && ( state == IDM_SEND_UPPER_DISPLACEMENT_Y ))
            {
                byteArrayToFloat(buffer, &decoded.value);
                decoded.type = UPPER_DISPLACMENT_Y;
            }

            else if (( byte == CDM_SEND_ROTATIONAL_POSITION_X) && ( state == IDM_SEND_ROTATIONAL_POSITION_X ))
            {
                byteArrayToFloat(buffer, &decoded.value);
                decoded.type = ROTATIONAL_POSITION_X;
            }

            else if (( byte == CDM_SEND_ROTATIONAL_POSITION_Y ) && ( state == IDM_SEND_ROTATIONAL_POSITION_Y ))
            {
                byteArrayToFloat(buffer, &decoded.value);
                decoded.type = ROTATIONAL_POSITION_Y;
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
