#include "cstring"
#include "conversions.h"

void byteArrayToFloat(FlyByte* buffer, float* val)
{
    memcpy(val, buffer, sizeof(*val));
}

void floatToByteArray(FlyByte* buffer, float* val)
{
    memcpy(buffer, val, sizeof(*val));
}


void byteArrayToInt(FlyByte* buffer, int* val)
{
    memcpy(val, buffer, sizeof(*val));
}

void intToByteArray(FlyByte* buffer, int* val)
{
    memcpy(buffer, val, sizeof(*val));
}



void zeroArray(void* target)
{
    memset(target, 0, sizeof(target));
}

void sliceArray(void* target, void* source, int begin, int end)
{
    memcpy(target,source+begin, end-begin+1);
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
