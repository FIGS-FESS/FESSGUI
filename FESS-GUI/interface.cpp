// Custom Libraries
#include "interface.h"

Interface::Interface(){}
Interface::~Interface(){}

//--------------------------------------------------------------------
// Public
//--------------------------------------------------------------------

void Interface::sync(){}

unsigned char Interface::pop()
{
    return popRX();
}

void Interface::pushCommand(unsigned char byte)
{
    pushTXChar(byte);
}

void Interface::pushData(int val)
{
    pushTXInt(val);
}

void Interface::pushData(float val)
{
    pushTXFloat(val);
}

void Interface::flush()
{
    flushRX();
}

bool Interface::empty()
{
    return emptyRX();
}

//--------------------------------------------------------------------
// Protected
//--------------------------------------------------------------------


// TX Methods
//--------------------------------------------------------------------
bool Interface::emptyTX()
{
    return tx.empty();
}

unsigned char Interface::popTX()
{
    unsigned char val = tx.front();
    tx.pop();
    return val;
}

void Interface::pushTXChar(unsigned char byt)
{
     tx.push(byt);
}

void Interface::pushTXInt(int val)
{
    unsigned char *bytes = reinterpret_cast<unsigned char *>(&val);

    tx.push(bytes[0]);
    tx.push(bytes[1]);
    tx.push(bytes[2]);
    tx.push(bytes[3]);
}

void Interface::pushTXFloat(float val)
{
    unsigned char *bytes = reinterpret_cast<unsigned char *>(&val);

    tx.push(bytes[0]);
    tx.push(bytes[1]);
    tx.push(bytes[2]);
    tx.push(bytes[3]);
}

void Interface::flushTX()
{
    std::queue<unsigned char> empty;
    std::swap(tx, empty);
}

// RX Methods
//--------------------------------------------------------------------
bool Interface::emptyRX()
{
    return rx.empty();
}

unsigned char Interface::popRX()
{
    unsigned char val = rx.front();
    rx.pop();
    return val;
}

void Interface::pushRXChar(unsigned char byt)
{
     rx.push(byt);
}

void Interface::pushRXInt(int val)
{
    unsigned char *bytes = reinterpret_cast<unsigned char *>(&val);

    rx.push(bytes[0]);
    rx.push(bytes[1]);
    rx.push(bytes[2]);
    rx.push(bytes[3]);
}

void Interface::pushRXFloat(float val)
{
    unsigned char *bytes = reinterpret_cast<unsigned char *>(&val);

    rx.push(bytes[0]);
    rx.push(bytes[1]);
    rx.push(bytes[2]);
    rx.push(bytes[3]);
}

void Interface::flushRX()
{
    std::queue<unsigned char> empty;
    std::swap(rx, empty);
}
