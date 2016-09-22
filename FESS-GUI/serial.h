#ifndef FLY_SERIAL_H
#define FLY_SERIAL_H

// C Libraries
#include <queue>

// QT Libraries
#include <QSerialPort>

// Custom Libraries

class Serial
{
    public:
        Serial();
        ~Serial();

        char pop();
        void push(char);

        bool getInterfaces();

        bool setInterfaces(int);
        bool setBaudRate(int);
        bool setParity(int);
        bool setFlowControl(int);
        bool setDataBits(int);
        bool setStopBits(int);
        void setDefaults();

    private:
        int  interfac;
        int  baudrate;
        char parity;
        char flowctrl;
        char databits;
        char stopbits;

        std::queue<char> in;
        std::queue<char> out;

        QSerialPort s;
};

#endif // FLY_SERIAL_H
