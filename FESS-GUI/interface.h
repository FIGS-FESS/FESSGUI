#ifndef INTERFACE_H
#define INTERFACE_H

// C/C++ Libraries
#include <queue>

class Interface
{
    public: // Used to get and recieve data from an interface

        Interface();
        ~Interface();

        virtual void sync();
        virtual void startDevice();
        virtual void stopDevice();

        bool empty();
        void flush();
        void pushData(int);
        void pushData(float);
        void pushCommand(unsigned char);
        unsigned char pop();

        bool emptyTX();
        void flushTX();

        bool emptyRX();
        void flushRX();

    protected: // For use by subclasses to manage queues

        // TX
        unsigned char popTX();
        void pushTXChar(unsigned char byt);
        void pushTXInt(int val);
        void pushTXFloat(float val);

        // RX
        unsigned char popRX();
        void pushRXChar(unsigned char byt);
        void pushRXInt(int val);
        void pushRXFloat(float val);


    private:
        std::queue<unsigned char> rx;
        std::queue<unsigned char> tx;
};

#endif // INTERFACE_H
