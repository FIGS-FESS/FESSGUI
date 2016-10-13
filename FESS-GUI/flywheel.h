#ifndef FLYWHEEL_H
#define FLYWHEEL_H

// C++ Libraries
#include <queue>

// Custom Libraries
#include "interface.h"

class Flywheel
{
    public:
        Flywheel(Interface *inter);

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

        Interface *interface;
        std::queue<float> vel;
        std::queue<float> acc;
        std::queue<float> jer;
        std::queue<float> udx;
        std::queue<float> udy;
        std::queue<float> ldx;
        std::queue<float> ldy;

        // Private Setters

        void setDefaults();

        void sync();

        // Helper Functions

        float getData();

        void sendData(float);
};

#endif // FLYWHEEL_H
