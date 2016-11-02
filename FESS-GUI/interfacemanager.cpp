#include "interfacemanager.h"

interfaceManager::interfaceManager()
{}

interfaceManager::~interfaceManager()
{}

void interfaceManager::findSerialDevices()
{
    serial_port_list = QSerialPortInfo::availablePorts();
    serial_list_size = serial_port_list.size();
}

CommonDeviceInterface* interfaceManager::getCurrentDevice()
{

}
