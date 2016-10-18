#ifndef INTERFACE_H
#define INTERFACE_H

// C++ Libraries
#include <queue>

class Interface
{
    public: // Used to get and recieve data from an interface

        Interface();
        ~Interface();

        virtual void sync();

        bool empty();
        void flush();
        void pushInt(int);
        void pushFloat(float);
        void pushChar(unsigned char);
        unsigned char pop();

    protected: // For use by subclasses to manage queues

        // TX
        bool emptyTX();
        unsigned char popTX();
        void pushTXChar(unsigned char byt);
        void pushTXInt(int val);
        void pushTXFloat(float val);
        void flushTX();

        // RX
        bool emptyRX();
        unsigned char popRX();
        void pushRXChar(unsigned char byt);
        void pushRXInt(int val);
        void pushRXFloat(float val);
        void flushRX();

    private:
        std::queue<unsigned char> rx;
        std::queue<unsigned char> tx;
};

#endif // INTERFACE_H
