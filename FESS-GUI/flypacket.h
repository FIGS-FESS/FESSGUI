#ifndef FLYPACKETLIB_H
#define FLYPACKETLIB_H

// Machine Command Codes
//------------------------------------------------
#define ICM_START                       0b00000001
#define ICM_STOP                        0b00000010
#define ICM_EMERGENCY_STOP              0b00000011
#define ICM_SET_VELOCITY                0b00000100
#define ICM_SET_ACCELERATION            0b00000101
#define ICM_SET_JERK                    0b00000110

#define CCM_START                       0b10000001
#define CCM_STOP                        0b10000010
#define CCM_EMERGENCY_STOP              0b10000011
#define CCM_SET_VELOCITY                0b10000100
#define CCM_SET_ACCELERATION            0b10000101
#define CCM_SET_JERK                    0b10000110

// Controller Command Codes
//------------------------------------------------
#define ICC_ERROR                       0b00100001
#define CCC_ERROR                       0b10100001

// Machine Data Codes
//------------------------------------------------
#define IDM_SEND_NULL                   0b00000000
#define IDM_SEND_VELOCITY               0b01000001
#define IDM_SEND_ACCELERATION           0b01000010
#define IDM_SEND_JERK                   0b01000011
#define IDM_SEND_LOWER_DISPLACEMENT_X   0b01000100
#define IDM_SEND_LOWER_DISPLACEMENT_Y   0b01000101
#define IDM_SEND_UPPER_DISPLACEMENT_X   0b01000110
#define IDM_SEND_UPPER_DISPLACEMENT_Y   0b01000111
#define IDM_SEND_ROTATIONAL_POSITION_X  0b01001000
#define IDM_SEND_ROTATIONAL_POSITION_Y  0b01001001

#define CDM_SEND_NULL                   0b10000000
#define CDM_SEND_VELOCITY               0b11000001
#define CDM_SEND_ACCELERATION           0b11000010
#define CDM_SEND_JERK                   0b11000011
#define CDM_SEND_LOWER_DISPLACEMENT_X   0b11000100
#define CDM_SEND_LOWER_DISPLACEMENT_Y   0b11000101
#define CDM_SEND_UPPER_DISPLACEMENT_X   0b11000110
#define CDM_SEND_UPPER_DISPLACEMENT_Y   0b11000111
#define CDM_SEND_ROTATIONAL_POSITION_X  0b11001000
#define CDM_SEND_ROTATIONAL_POSITION_Y  0b11001001

#define IDM_CMD_DIFFERENCE              0b10000000

// Internal Size Constants
//------------------------------------------------

#define HEADER_SIZE             1
#define FOOTER_SIZE             1
#define MAX_PAYLOAD             4

#define PACKET_BEGINNING        0
#define PACKET_END              HEADER_SIZE + MAX_PAYLOAD

#define DATA_BEGINNING          HEADER_SIZE
#define DATA_END                PACKET_END - FOOTER_SIZE

#define PACKET_SIZE             PACKET_END + FOOTER_SIZE

// Error Types
//------------------------------------------------
#define NO_ERROR                0

#include "conversions.h"

class FlyPacket
{
  public:
    FlyPacket();
    FlyPacket(FlyByte, int);
    FlyPacket(FlyByte, float);

    ~FlyPacket();

    // Setters
    void setValue(int);
    void setValue(float);
    void setCommand(FlyByte);
    void writeByte(FlyByte);

    // Getters
    int getInt();
    float getFloat();
    FlyByte readByte();
    FlyByte getCommand();

    // Universal
    void reset();
    bool isWriteable();
    bool isReadable();

    bool isValidPacket();
    bool isValidCommand();

   private:
    bool invalidCommand;
    bool readComplete;
    bool writeComplete;

    FlyByte byteArrayPosition;
    FlyByte byteArray[PACKET_SIZE];

    void checkCommand();
};


#endif // FLYPACKETLIB_H
