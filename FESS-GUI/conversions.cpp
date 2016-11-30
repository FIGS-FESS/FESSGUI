#include "conversions.h"

float byteArrayToFloat(FlyByte* buffer)
{
    float val;
    memcpy(&val, buffer, sizeof(val));
    return val;
}

void floatToByteArray(FlyByte* buffer, float* val)
{
    memcpy(buffer, val, sizeof(*val));
}


int byteArrayToInt(FlyByte* buffer)
{
    int val;
    memcpy(&val, buffer, sizeof(val));
    return val;
}

void intToByteArray(FlyByte* buffer, int* val)
{
    memcpy(buffer, val, sizeof(*val));
}



void zeroArray(void* target, size_t size)
{
    memset(target, 0, size);
}



double radsPerSecondToRPM(double rads)
{
    return rads * (60 / TAU);
}

double RPMtoRadsPerSecond(double RPM)
{
    return RPM * (TAU / 60);
}


float derivative(float value, float prev)
{
    return value-prev;
}

float refreshRateToMS(int rate)
{
    return 1000.0/rate;
}
