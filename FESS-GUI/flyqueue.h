#ifndef FLYQUEUE_H
#define FLYQUEUE_H

#include <deque>
#include <flypacket.h>

class FlyQueue
{
    public:
        FlyQueue();
        ~FlyQueue();

        void clear();
        void reset();
        void setSize(int);

        bool isEmpty();

        FlyPacket pop();
        void push(FlyPacket);

    private:
        unsigned int maximumSize;

        FlyPacket currentPacket;
        std::deque<FlyPacket> internalBuffer;

};

#endif // FLYQUEUE_H
