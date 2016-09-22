// C Libraries
#include <queue>

// QT Libraries
#include <QtGui>
#include <QSerialPort>
#include <QSerialPortInfo>

// Custom Libraries
#include "serial.h"



Serial::Serial()
{
    setDefaults();

    qDebug() << "Serial: Searching for Devices";

    // Example use QSerialPortInfo
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        qDebug() << "Name : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();

        // Example use QSerialPort

        s.setPort(info);

        if (s.open(QIODevice::ReadWrite))
        {
            s.putChar('a');
            s.flush();

            //if (serial.readyRead())
            {
                qDebug() << "Read:" << s.readAll();
            }

            s.close();
        }
    }

    qDebug() << "Serial: Done";

}

Serial::~Serial()
{

}

char Serial::pop()
{
    char val = 0;

    if(!in.empty())
    {
        val = in.front();
        in.pop();
    }

    return val;
}


void Serial::push(char byt)
{
    out.push(byt);
}

bool Serial::setBaudRate(int rate)
{
    s.setBaudRate(rate);
}

bool Serial::setParity(int pari)
{
    switch(pari)
    {
        case 0:
        {
            s.setParity(QSerialPort::NoParity);
            break;
        }
        case 1:
        {
            s.setParity(QSerialPort::OddParity);
            break;
        }

        case 2:
        {
            s.setParity(QSerialPort::EvenParity);
            break;
        }
        default:
        {
            // Error
        }
    }
}

bool Serial::setFlowControl(int flow)
{
    switch(flow)
    {
        case 0:
        {
            s.setFlowControl(QSerialPort::NoFlowControl);
            break;
        }
        case 1:
        {
            s.setFlowControl(QSerialPort::HardwareControl);
            break;
        }

        case 2:
        {
            s.setFlowControl(QSerialPort::SoftwareControl);
            break;
        }
        default:
        {
            // Error
        }
    }
}

bool Serial::setDataBits(int bits)
{
    s.setDataBits(bits);
}

bool Serial::setStopBits(int bits)
{
    s.setStopBits(bits);
}

void Serial::setDefaults()
{
    setInterfaces(-1);
    setBaudRate(9600);
    setParity(0);
    setFlowControl(0);
    setDataBits(8);
    setStopBits(1);
}
