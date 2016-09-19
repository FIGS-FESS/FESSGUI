#include <QSerialPort>
#include <QSerialPortInfo>

#include <QtGui>

#include "serial.h"



Serial::Serial()
{
    len = 0;

    qDebug() << "Serial: Searching for Devices";

    // Example use QSerialPortInfo
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        qDebug() << "Name : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();

        // Example use QSerialPort
        QSerialPort s;
        s.setPort(info);
        s.setBaudRate(QSerialPort::Baud9600);
        s.setParity(QSerialPort::NoParity);
        s.setFlowControl(QSerialPort::NoFlowControl);
        s.setDataBits(QSerialPort::Data8);
        s.setStopBits(QSerialPort::OneStop);

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

bool Serial::append(char x)
{
    qDebug() << x;
    /*
    if (len < MAX)
    {
        buffer[len] = x;
        len++;
        return true;
    }

    else
    {
        return false;
    }*/
    return false;
}
