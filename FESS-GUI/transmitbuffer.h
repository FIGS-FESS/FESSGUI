#ifndef TRANSMITBUFFER_H
#define TRANSMITBUFFER_H

// C++ Libaries
#include <deque>

class TransmitBuffer
{
    public:
        TransmitBuffer();
        ~TransmitBuffer();

        void pushInt(int);
        void pushFloat(float);
        void pushChar(unsigned char);
        void pushFrontChar(unsigned char);

        int popInt();
        float popFloat();
        unsigned char popChar();

        void flush();
        bool empty();

    private:
        std::deque<unsigned char> buffer;

};

#endif // TRANSMITBUFFER_H
