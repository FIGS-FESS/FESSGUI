#include "commoninterfacemanager.h"

CommonInterfaceManager::CommonInterfaceManager()
{
    currentDevice = NULL;
}

CommonDeviceInterface* CommonInterfaceManager::getCurrentInterface()
{
    return currentDevice;
}

bool CommonInterfaceManager::isADeviceSet()
{
     if(currentDevice != NULL)
     {
         return true;
     }
     else
     {
         return false;
     }
}

void CommonInterfaceManager::setCurrentInterface(CommonDeviceInterface* newInterface)
{
    currentDevice = newInterface;
}

void CommonInterfaceManager::closeCurrentInterface()
{
    delete currentDevice;
    currentDevice = NULL;
}
