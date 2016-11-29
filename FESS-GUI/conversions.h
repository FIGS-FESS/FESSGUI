#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#define TAU	6.283185307179586476925286766559005768394

#include "cstring"


typedef unsigned char FlyByte;


void byteArrayToFloat(FlyByte*, float*);
void floatToByteArray(FlyByte*, float*);

void byteArrayToInt(FlyByte*, int*);
void intToByteArray(FlyByte*, int*);


void zeroArray(void* , size_t);
void sliceArray(void*, void*, unsigned int, unsigned int);


double radsPerSecondToRPM(double);
double RPMtoRadsPerSecond(double);


float derivative(float, float);


float refreshRateToMS(int);

#endif // CONVERSIONS_H
