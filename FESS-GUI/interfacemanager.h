#ifndef INTERFACEMANAGER_H
#define INTERFACEMANAGER_H

// C/C++ Libraries
#include <string>

// QT Libraries
#include <QSerialPortInfo>

class interfaceManager
{
    public:
        interfaceManager();
        ~interfaceManager();

        void findSerialDevices();

    private:

        int serial_list_size;
        QSerialPortInfo* port;
        QList<QSerialPortInfo> serial_port_list;
};

#endif // INTERFACEMANAGER_H
