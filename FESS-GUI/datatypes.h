#ifndef DATATYPES_H
#define DATATYPES_H

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
   flybyte type;
   float value;
};

typedef struct flypacket flypacket;


#endif // DATATYPES_H

