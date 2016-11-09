#ifndef DATATYPES_H
#define DATATYPES_H

#define NULL_DATA               0

#define NULL_PACKET             0
#define DATA_PACKET             1
#define COMM_PACKET             2
#define ERRO_PACKET             3

#define NULL_TYPE               0
#define VELOCITY                1
#define ACCELERATION            2
#define JERK                    3
#define LOWER_DISPLACMENT_X     4
#define LOWER_DISPLACMENT_Y     5
#define UPPER_DISPLACMENT_X     6
#define UPPER_DISPLACMENT_Y     7
#define ROTATIONAL_POSITION_X   8
#define ROTATIONAL_POSITION_Y   9

typedef unsigned char flybyte;

struct flypacket
{
   flybyte packetType;
   flybyte dataType;
   float   dataValue;
};

typedef struct flypacket flypacket;


#endif // DATATYPES_H

