#include "interface.h"

#include <QtGui>
#include <QApplication>


unsigned char Interface::pop()
{
    if(!in.empty())
    {
        char val = in.front();
        in.pop();
        return val;
    }
    else
    {
        return 0;
    }
}


void Interface::push(unsigned char byte)
{
    out.push(byte);
}

void Interface::push(int val)
{
    unsigned char *bytes = reinterpret_cast<unsigned char *>(&val);

    push(bytes[0]);
    push(bytes[1]);
    push(bytes[2]);
    push(bytes[3]);
}

void Interface::push(float val)
{
    unsigned char *bytes = reinterpret_cast<unsigned char *>(&val);

    qDebug() << "INT: " << bytes[0];
    qDebug() << "INT: " << bytes[1];
    qDebug() << "INT: " << bytes[2];
    qDebug() << "INT: " << bytes[3];

    push(bytes[0]);
    push(bytes[1]);
    push(bytes[2]);
    push(bytes[3]);
}

void Interface::flush()
{
    while(!in.empty())
    {
        in.pop();
    }
}

bool Interface::internalEmpty()
{
    return out.empty();
}

unsigned char Interface::internalPop()
{
    if(!out.empty())
    {
        unsigned char val = out.front();
        out.pop();
        return val;
    }
}

void Interface::internalPush(unsigned char byt)
{
     in.push(byt);
}


