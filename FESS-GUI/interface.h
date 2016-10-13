#ifndef INTERFACE_H
#define INTERFACE_H

// C++ Libraries
#include <queue>

class Interface
{
    public:
        // Used to get and recieve data from an interface
        unsigned char pop();
        void flush();

        void push(int);
        void push(float);
        void push(unsigned char);

    protected:
        // For use by subclasses to manage queues
        bool internalEmpty();
        unsigned char internalPop();
        void internalPush(unsigned char);

    private:
        std::queue<unsigned char> in;
        std::queue<unsigned char> out;
};

#endif // INTERFACE_H
