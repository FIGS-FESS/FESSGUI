#include "commoninterfacemanager.h"

/*! \brief CommonInterfaceManager::CommonInterfaceManager Set the device to NULL.
 */
CommonInterfaceManager::CommonInterfaceManager()
{
    currentDevice = NULL;
}

/*! \brief CommonInterfaceManager::~CommonInterfaceManager Deletes the current device.
 */
CommonInterfaceManager::~CommonInterfaceManager()
{
    delete currentDevice;
}

/*! \brief CommonInterfaceManager::getCurrentInterface Get the current interface.
 *  \return CommonDeviceInterface* (CommonDeviceInterface Instance Pointer,NULL)
 */
CommonDeviceInterface* CommonInterfaceManager::getCurrentInterface()
{
    return currentDevice;
}

/*! \brief CommonInterfaceManager::isADeviceSet Determines if a device has been set in the menu.
 *  \return bool (true=Yes, false=No)
 */
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

/*! \brief CommonInterfaceManager::setCurrentInterface Sets the curret device interface.
 *  \param CommonDeviceInterface*
 */
void CommonInterfaceManager::setCurrentInterface(CommonDeviceInterface* newInterface)
{
    delete currentDevice;
    currentDevice = newInterface;
}

/*! \brief CommonInterfaceManager::closeCurrentInterface Closes the current interface.
 */
void CommonInterfaceManager::closeCurrentInterface()
{
    delete currentDevice;
    currentDevice = NULL;
}
