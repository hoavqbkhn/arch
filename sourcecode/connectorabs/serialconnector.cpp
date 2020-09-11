#include "serialconnector.h"
#include "logger/logger.h"

#include <QByteArray>


SerialConnector::SerialConnector(const std::string& portName,
                                 qint32 baudrate)
    : mPortName(portName), mBaudRate(baudrate)
{
}

SerialConnector::~SerialConnector()
{
}

bool SerialConnector::startIO()
{
    mSerialPort = QSharedPointer<QSerialPort>(new QSerialPort());
    mSerialPort->setPortName(QString::fromStdString(mPortName));

    if (!mSerialPort->setBaudRate(mBaudRate))
    {
        LOG_ERROR("Error setting Baud");
        return false;
    }

    if (!mSerialPort->setParity(mParity))
    {
        LOG_ERROR("Error setting Parity");
        return false;
    }

    if (!mSerialPort->setDataBits(mDataBits))
    {
        LOG_ERROR("Error setting Data");
        return false;
    }

    if (!mSerialPort->setStopBits(mStopBits))
    {
        LOG_ERROR("Error setting Stopbits");
        return false;
    }

    if (!mSerialPort->setFlowControl(mFlowControl))
    {
        LOG_ERROR("Error setting Flow");
        return false;
    }

    if (!mSerialPort->open(QIODevice::ReadWrite))
    {
        setIsConnected(false);
        LOG_ERROR("Failed to open port %s, error: %s",
                  mSerialPort->portName().toStdString().c_str(),
                  mSerialPort->errorString().toStdString().c_str());
        return false;
    }
    else
    {
        setIsConnected(true);
        LOG_DEBUG("Success to open port %s", mSerialPort->portName().toStdString().c_str());
    }

    connect(mSerialPort.data(), &QSerialPort::readyRead, this, &SerialConnector::handleReadyRead);
    return true;
}

bool SerialConnector::stopIO()
{
    if (mSerialPort)
    {
        mSerialPort->close();
    }
    else
    {
        LOG_DEBUG("mSerialPort is null");
        return false;
    }

    if (mSerialPort->isOpen())
    {
        return false;
    }

    setIsConnected(false);
    return true;
}

void SerialConnector::send(const char* data2send, int length)
{
    QByteArray writeData(data2send, length);
    const qint64 bytesWritten = mSerialPort->write(writeData);

    if ((bytesWritten == -1) || (bytesWritten != writeData.size()))
    {
        LOG_ERROR("Could not send serial data to port: %s", mPortName.c_str());
    }
}

void SerialConnector::send(std::string target, const char* data2send, int length)
{
    //TODO
    (void) target;
    (void) data2send;
    (void) length;
}

void SerialConnector::handleReadyRead()
{
    QByteArray data = mSerialPort->readAll();
    emit IOConnector::handleIOMessage(data.data(), data.size());
}

void SerialConnector::setFlowControl(const QSerialPort::FlowControl& flowControl)
{
    mFlowControl = flowControl;
}

void SerialConnector::setDataBits(const QSerialPort::DataBits& dataBits)
{
    mDataBits = dataBits;
}

void SerialConnector::setStopBits(const QSerialPort::StopBits& stopBits)
{
    mStopBits = stopBits;
}

void SerialConnector::setParity(const QSerialPort::Parity& parity)
{
    mParity = parity;
}

