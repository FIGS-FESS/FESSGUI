/*! \brief FlyQueue Class
 *  A wrapper to allow for reuse on the microcontroller
 */

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

        FlyPacket operator[](const unsigned int);

    private:
        unsigned int maximumSize;

        FlyPacket currentPacket;
        std::deque<FlyPacket> internalBuffer;

};

#endif // FLYQUEUE_H
