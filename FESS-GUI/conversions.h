#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#include <datatypes.h>

void byteArrayToFloat(flybyte*, float*);
void floatToByteArray(flybyte*, float*);

void byteArrayToInt(flybyte*, int*);
void intToByteArray(flybyte*, int*);

double radsPerSecondToRPM(double);
double RPMtoRadsPerSecond(double);

float derivative(float, float);

float refreshRateToMS(int);

#endif // CONVERSIONS_H
