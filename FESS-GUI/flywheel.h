#ifndef FLYWHEEL_H
#define FLYWHEEL_H

#include "serial.h"

class Flywheel
{
    public:
        Flywheel();
        Flywheel(Serial &swsettings);

        ~Flywheel();

        // Setters

        void setV(float vel);

        void setA(float acc);

        void setJ(float jer);

        void setVA(float vel, float acc);

        void setVJ(float vel, float jer);

        void setAJ(float acc, float jer);

        void setVAJ(float vel, float acc, float jer);

        // Getters

        float getV();

        float getA();

        float getJ();

        float getLDX();

        float getLDY();

        float getUPX();

        float getUPY();

    private:

        // Private Variables

        float vel;
        float acc;
        float jer;
        float udx;
        float udy;
        float ldx;
        float ldy;
        Serial serial;

        // Private Setters

        void setDefaults();

        void setVP(float x);

        void setAP(float x);

        void setJP(float x);

        void setVAP(float x, float y);

        void setVJP(float x, float y);

        void setAJP(float x, float y);

        void setVAJP(float x, float y, float z);
};

#endif // FLYWHEEL_H
