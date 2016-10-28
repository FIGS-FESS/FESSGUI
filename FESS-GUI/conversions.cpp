#include "qmath.h"
#include "string.h"
#include "conversions.h"

void byteArrayToFloat(flybyte* buffer, float* val)
{
    memcpy(val, buffer, sizeof(*val));
}

void floatToByteArray(flybyte* buffer, float* val)
{
    memcpy(buffer, val, sizeof(*val));
}


void byteArrayToInt(flybyte* buffer, int* val)
{
    memcpy(val, buffer, sizeof(*val));
}

void intToByteArray(flybyte* buffer, int* val)
{
    memcpy(buffer, val, sizeof(*val));
}


double radsPerSecondToRPM(double rads)
{
    return rads * (60 / (2 * M_PI)); //M_PI is defined in <qmath.h>
}

double RPMtoRadsPerSecond(double RPM)
{
    return RPM * ((2 * M_PI) / 60);
}
