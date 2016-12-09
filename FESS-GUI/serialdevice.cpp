// Custom Libraries --------------------------------------------------
#include "serialdevice.h"

//--------------------------------------------------------------------
// SerialDevice Constructors
//--------------------------------------------------------------------

/*! \brief SerialDevice::SerialDevice Creates a new serial instance and configures it with the default values.
 */
SerialDevice::SerialDevice()
{
    device = new QSerialPort();
    setDefaults();
}

/*! \brief SerialDevice::SerialDevice Creates a new serial instance and configures it with the default values.
    \param QSerialPortInfo (Serial Port Instance)
*/
SerialDevice::SerialDevice(QSerialPortInfo port)
{
    device = new QSerialPort();
    setDefaults();
    setPort(port);
}

/*! \brief SerialDevice::SerialDevice Creates a new serial instance and configures it with the default values.
    \param QString (Windows Example: COMM1, *INX Example: /dev/ttyUSB0)
*/
SerialDevice::SerialDevice(QString path)
{
    device = new QSerialPort(path);
    setDefaults();
}

//--------------------------------------------------------------------
// SerialDevice Destructors
//--------------------------------------------------------------------

/*! \brief SerialDevice::~SerialDevice Stops transmissions and deletes the serial instance.
*/
SerialDevice::~SerialDevice()
{
    stopDevice();
    delete device;
}

//--------------------------------------------------------------------
// Public
//--------------------------------------------------------------------
// SerialDevice Device Settings --------------------------------------------

/*! \brief SerialDevice::setPort Sets the serial port.
    \param QSerialPortInfo Instance
*/
void SerialDevice::setPort(QSerialPortInfo port)
{
    device->setPort(port);
}

/*! \brief SerialDevice::setBaudRate Changes the serial device's baud rate
    \param int (0-9999999999)
*/
void SerialDevice::setBaudRate(int rate)
{
    device->setBaudRate(rate,QSerialPort::AllDirections);
}

/*! \brief SerialDevice::setParity Changes the serial device's parity
    \param int (0=NO, 1=ODD, 2=EVEN)
*/
void SerialDevice::setParity(int pari)
{
    switch(pari)
    {
        case 0:
        {
            device->setParity(QSerialPort::NoParity);
            break;
        }
        case 1:
        {
            device->setParity(QSerialPort::OddParity);
            break;
        }

        case 2:
        {
            device->setParity(QSerialPort::EvenParity);
            break;
        }
        default:
        {
            break;
        }
    }
}

/*! \brief SerialDevice::setFlowControl Changes the serial device's flow control
    \param int (0=NONE, 1=HW, 2=SW)
*/
void SerialDevice::setFlowControl(int flow)
{
    switch(flow)
    {
        case 0:
        {
            device->setFlowControl(QSerialPort::NoFlowControl);
            break;
        }
        case 1:
        {
            device->setFlowControl(QSerialPort::HardwareControl);
            break;
        }

        case 2:
        {
            device->setFlowControl(QSerialPort::SoftwareControl);
            break;
        }
        default:
        {
            break;
        }
    }
}

/*! \brief SerialDevice::setDataBits Changes the serial device's number of data bits.
    \param int (5-8)
*/
void SerialDevice::setDataBits(int bits)
{
    switch(bits)
    {
        case 5:
        {
            device->setDataBits(QSerialPort::Data5);
            break;
        }

        case 6:
        {
            device->setDataBits(QSerialPort::Data6);
            break;
        }
        case 7:
        {
            device->setDataBits(QSerialPort::Data7);
            break;
        }

        case 8:
        {
            device->setDataBits(QSerialPort::Data8);
            break;
        }
        default:
        {
            break;
        }
    }
}

/*! \brief SerialDevice::setStopBits Changes the serial device's number of stop bits.
    \param int (1=1, 2=1.5, 3=2)
*/
void SerialDevice::setStopBits(int bits)
{
    switch(bits)
    {
        case 1:
        {
            device->setStopBits(QSerialPort::OneStop);
            break;
        }

        case 2:
        {
            device->setStopBits(QSerialPort::OneAndHalfStop);
            break;
        }

        case 3:
        {
            device->setStopBits(QSerialPort::TwoStop);
            break;
        }

        default:
        {
            break;
        }
    }
}


//--------------------------------------------------------------------
// Private
//--------------------------------------------------------------------

// SerialDevice Device Send and Receive ----------------------------------

/*! \brief SerialDevice::sendTX Read bytes from the TX Transmit Buffer into the serial device.
 */
void SerialDevice::sendTX()
{
    while(tx.bytesAvailable() == true)
    {
        device->putChar(tx.popByte());
    }

    device->waitForBytesWritten(0);
}

/*! \brief SerialDevice::readRX Read bytes from the Serial Device into the RX Transmit Buffer.
 */
void SerialDevice::readRX()
{
    device->waitForReadyRead(0);

    QByteArray in = device->readAll();

    for (int i = 0; i < in.size(); i++)
    {
        rx.pushByte(in[i]);
    }
}


//--------------------------------------------------------------------
// Interface Overedload Functions
//--------------------------------------------------------------------

/*! \brief SerialDevice::syncRX Is the serial interface's implementation of syncRX.
 * Same functionality as readRX.
 */
void SerialDevice::syncRX()
{
    readRX();
}

/*! \brief SerialDevice::syncRX Is the serial interface's implementation of syncRX.
 * Same functionality as sendTX.
 */
void SerialDevice::syncTX()
{
    sendTX();
}

/*! \brief SerialDevice::isReady Is the serial interface's implementation of isReady.
 * Get the status of the serial interface
 *  \return bool (true=Ready, false=Not Ready)
 */
bool SerialDevice::isReady()
{
    return statusReady;
}

/*! \brief SerialDevice::startDevice Is the serial interface's implementation of startDevice.
 * Starts the serial interface, clears its buffers and updates status
 *  \return bool (true=Started, false=Not Ready)
 */
bool SerialDevice::startDevice()
{
    statusReady = device->open(QIODevice::ReadWrite);

    if (statusReady == true)
    {
        device->clear();
    }

    return statusReady;
}

/*! \brief SerialDevice::stopDevice Is the serial interface's implementation of stopDevice.
 * Stops the serial interface, empties the serial devices buffers, empties the Transmit Buffers and updates status
 */
void SerialDevice::stopDevice()
{
    if (statusReady == true)
    {

        statusReady = false;
        rx.flush();
        tx.flush();
        device->clear();
        device->close();
    }
}

/*! \brief SerialDevice::stopDevice Is the serial interface's implementation of setDefaults.
 * Sets the serial devices to the default values. (Rate=9600, Parity=None, Flow=None, Data=8, Stop=1)
 */
void SerialDevice::setDefaults()
{
    statusReady = false;
    setBaudRate(9600);
    setParity(0);
    setFlowControl(0);
    setDataBits(8);
    setStopBits(1);
}

/*! \brief SerialDevice::popByte Is the serial interface's implementation of popByte.
 *  \return FlyByte (From the RX Transmit Buffer).
 */
FlyByte SerialDevice::popByte()
{
    return rx.popByte();
}

/*! \brief SerialDevice::popByte Is the serial interface's implementation of popPacket.
 *  \return FlyPacket (From the RX Transmit Buffer).
 */
FlyPacket SerialDevice::popPacket()
{
    return rx.popPacket();
}

/*! \brief SerialDevice::popByte Is the serial interface's implementation of pushByte.
 *  \param FlyByte (Adds it to the TX Transmit Buffer).
 */
void SerialDevice::pushByte(FlyByte dataByte)
{
    tx.pushByte(dataByte);
}

/*! \brief SerialDevice::popByte Is the serial interface's implementation of pushPacket.
 *  \param FlyPacket (Adds to the TX Transmit Buffer).
 */
void SerialDevice::pushPacket(FlyPacket dataPacket)
{
    tx.pushPacket(dataPacket);
}

/*! \brief SerialDevice::flushRX Is the serial interface's implementation of flushRX.
 *  Empties the RX Transmit Buffer
 */
void SerialDevice::flushRX()
{
    rx.flush();
}

/*! \brief SerialDevice::flushTX Is the serial interface's implementation of flushTX.
 *  Empties the TX Transmit Buffer
 */
void SerialDevice::flushTX()
{
    tx.flush();
}

/*! \brief SerialDevice::empty Is the serial interface's implementation of empty.
 *  \return bool (true=Empty, false=Not Empty)
 */
bool SerialDevice::empty()
{
    return !rx.packetsAvailable();
}

/*! \brief SerialDevice::name Is the serial interface's implementation of name.
 *  \return Qstring (Serial Device Port)
 */
QString SerialDevice::name()
{
    if (device)
    {
        return QString("Serial Device: %1").arg(device->portName());
    }
    else
    {
        return QString("Serial Device: None");
    }
}
