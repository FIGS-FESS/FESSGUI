#include "string.h"
#include "conversionlib.h"

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


