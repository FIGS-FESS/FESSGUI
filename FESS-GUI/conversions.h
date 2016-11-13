#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#define TAU	6.283185307179586476925286766559005768394

typedef unsigned char flybyte;


void byteArrayToFloat(flybyte*, float*);
void floatToByteArray(flybyte*, float*);

void byteArrayToInt(flybyte*, int*);
void intToByteArray(flybyte*, int*);


void zeroArray(void*);
void sliceArray(void*, void*, int, int);


double radsPerSecondToRPM(double);
double RPMtoRadsPerSecond(double);


float derivative(float, float);


float refreshRateToMS(int);

#endif // CONVERSIONS_H
