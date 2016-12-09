#include "commoninterfaceselector.h"

/*! \brief CommonInterfaceSelector::CommonInterfaceSelector
 * GUI window for configuring devices.
 *  \param CommonInterfaceManager* (Interface Manager Instance)
 *  \param QWidget (Parent Window)
 */

CommonInterfaceSelector::CommonInterfaceSelector(CommonInterfaceManager* commonManager, QWidget *parent) : QDialog(parent), ui(new Ui::CommonInterfaceSelector)
{
    ui->setupUi(this);
    interfaceManager = commonManager;

    serialPortIndex = -1;
    serialPortTextValue = ui->serialPortCombo->currentText();

    errorHandler = new QErrorMessage(this);
    errorHandler->setWindowTitle("FlyCam - Selection Error");

    setUpSignals();
    setSerialPortsComboBox();
}

/*! \brief CommonInterfaceSelector::~CommonInterfaceSelector
 *  Destructor deletes ui and errorHandler objects.
 */
CommonInterfaceSelector::~CommonInterfaceSelector()
{
    delete errorHandler;
    delete ui;
}

// Private Slots

/*! \brief CommonInterfaceSelector::closeWindow Closes the selection windows and invokes the destructor.
 */
void CommonInterfaceSelector::closeWindow()
{
    this->close();
}

/*! \brief CommonInterfaceSelector::setUpSingals Binds ui buttons to functions.
 */
void CommonInterfaceSelector::setUpSignals()
{
    connect(ui->demoButtonSet,    SIGNAL(clicked()), this, SLOT(demoButtonSetClicked()));
    connect(ui->demoButtonCancel, SIGNAL(clicked()), this, SLOT(demoButtonCancelClicked()));

    connect(ui->serialButtonSet,    SIGNAL(clicked()), this, SLOT(serialButtonSetClicked()));
    connect(ui->serialButtonCancel, SIGNAL(clicked()), this, SLOT(serialButtonCancelClicked()));

    connect(ui->serialPortCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(setSerialPortsComboBoxIndex(int)));
    connect(ui->serialPortCombo, SIGNAL(editTextChanged(const QString)), this, SLOT(setSerialPortsComboBoxText(const QString)));
}

/*! \brief CommonInterfaceSelector::setSerialPortComboBox Interates over available serial interfaces and adds them to a drop down box.
 */
void CommonInterfaceSelector::setSerialPortsComboBox()
{
    serialPortList = QSerialPortInfo::availablePorts();

    for (int i = 0; i < serialPortList.size(); i++)
    {
        ui->serialPortCombo->insertItem(i,serialPortList[i].portName());
    }
}

// Private Slots

/*! \brief CommonInterfaceSelector::demoButtonSetClicked Creates a demo object and passes it to the interface manager.
 */
void CommonInterfaceSelector::demoButtonSetClicked()
{
    int demo_port_index = ui->demoPortCombo->currentIndex();

    switch(demo_port_index)
    {
        case 0:
        {
            DemoDevice* deviceInterface = new DemoDevice();
            interfaceManager->setCurrentInterface(deviceInterface);
            break;
        }
        default: break;
    }

    closeWindow();
}

/*! \brief CommonInterfaceSelector::demoButtonCancelClicked Discards the changes made in the selection menu and closes the window.
 */
void CommonInterfaceSelector::demoButtonCancelClicked()
{
    closeWindow();
}

/*! \brief CommonInterfaceSelector::serialButtonClicked Creates a serial object with the selected settings and passed it to the interface manager.
 */
void CommonInterfaceSelector::serialButtonSetClicked()
{
    SerialDevice* deviceInterface = nullptr;

    int serialBaudRate = ui->serialBaudLine->text().toInt();
    int serialDataIndex = ui->serialDataCombo->currentIndex();
    int serialStopIndex = ui->serialStopCombo->currentIndex();
    int serialFlowIndex = ui->serialFlowCombo->currentIndex();
    int serialParityIndex = ui->serialParityCombo->currentIndex();

    if (serialPortIndex < 0)
    {
        deviceInterface = new SerialDevice(serialPortTextValue);
    }
    else
    {
        deviceInterface = new SerialDevice();
        deviceInterface->setPort(serialPortList[serialPortIndex]);
    }


    if (deviceInterface != NULL)
    {
        deviceInterface->setBaudRate(serialBaudRate);
        deviceInterface->setParity(serialParityIndex);
        deviceInterface->setDataBits(serialDataIndex+5);
        deviceInterface->setStopBits(serialStopIndex);
        deviceInterface->setFlowControl(serialFlowIndex);

        if (deviceInterface->startDevice() == true)
        {
            interfaceManager->setCurrentInterface(deviceInterface);
            deviceInterface->stopDevice();
            closeWindow();
        }

        else
        {
            errorHandler->showMessage("Unable to open the serial port. Please try: Checking your settings, Unplugging the device, Checking device permissions.");
            delete deviceInterface;
            deviceInterface = NULL;
        }
    }
    else
    {
        errorHandler->showMessage("Serial device could not be set as specified.");
    }
}

/*! \brief CommonInterfaceSelector::serialButtonCancelClicked Discards the changes made in the selection menu and closes the window.
 */
void CommonInterfaceSelector::serialButtonCancelClicked()
{
    closeWindow();
}

/*! \brief CommonInterfaceSelector::setSerialPortsComboBoxText Allows the user to enter devices into the device combo box the application didn't find.
 *  \param QString (The name of the device or path to the device)
 */
void CommonInterfaceSelector::setSerialPortsComboBoxText(const QString &text)
{
    serialPortIndex = -1;
    serialPortTextValue = text;
}

/*! \brief CommonInterfaceSelector::setSerialPortsComboBoxIndex Allows the interface to change the selection of drop down interfaces.
 *  \param int (Index of desired device)
 */
void CommonInterfaceSelector::setSerialPortsComboBoxIndex(int serialIndex)
{
    serialPortIndex = serialIndex;
}
