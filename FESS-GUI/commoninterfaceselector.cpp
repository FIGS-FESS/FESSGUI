#include "commoninterfaceselector.h"

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

CommonInterfaceSelector::~CommonInterfaceSelector()
{
    delete errorHandler;
    delete ui;
}

// Private Slots

void CommonInterfaceSelector::closeWindow()
{
    this->close();
}

void CommonInterfaceSelector::setUpSignals()
{
    connect(ui->demoButtonSet,    SIGNAL(clicked()), this, SLOT(demoButtonSetClicked()));
    connect(ui->demoButtonCancel, SIGNAL(clicked()), this, SLOT(demoButtonCancelClicked()));

    connect(ui->serialButtonSet,    SIGNAL(clicked()), this, SLOT(serialButtonSetClicked()));
    connect(ui->serialButtonCancel, SIGNAL(clicked()), this, SLOT(serialButtonCancelClicked()));

    connect(ui->serialPortCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(setSerialPortsComboBoxIndex(int)));
    connect(ui->serialPortCombo, SIGNAL(editTextChanged(const QString)), this, SLOT(setSerialPortsComboBoxText(const QString)));
}

void CommonInterfaceSelector::setSerialPortsComboBox()
{
    serialPortList = QSerialPortInfo::availablePorts();

    for (int i = 0; i < serialPortList.size(); i++)
    {
        ui->serialPortCombo->insertItem(i,serialPortList[i].portName());
    }
}

// Private Slots

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

void CommonInterfaceSelector::demoButtonCancelClicked()
{
    closeWindow();
}

void CommonInterfaceSelector::serialButtonSetClicked()
{
    SerialDevice* deviceInterface = NULL;

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

void CommonInterfaceSelector::serialButtonCancelClicked()
{
    closeWindow();
}

void CommonInterfaceSelector::setSerialPortsComboBoxText(const QString &text)
{
    serialPortIndex = -1;
    serialPortTextValue = text;
}

void CommonInterfaceSelector::setSerialPortsComboBoxIndex(int serialIndex)
{
    serialPortIndex = serialIndex;
}
