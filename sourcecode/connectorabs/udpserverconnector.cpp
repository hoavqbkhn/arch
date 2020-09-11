#include "udpserverconnector.h"

UdpServerConnector::UdpServerConnector(const std::string& udpIP, int localPort, int remotePort)
{
    mUdpIP = QString::fromStdString(udpIP);
    mLocalPort = localPort;
    mRemotePort = remotePort;
    mUdpSocket = QSharedPointer<QUdpSocket>(new QUdpSocket());
}

UdpServerConnector::~UdpServerConnector()
{
}

bool UdpServerConnector::startIO()
{
    connect(mUdpSocket.data(), &QUdpSocket::readyRead, this, &UdpServerConnector::handleReadyRead);

    if (!mUdpSocket->bind(mLocalPort))
    {
        LOG_ERROR("Failed to open udp port %s, error: %s",
                  mUdpIP.toStdString().c_str(),
                  mUdpSocket->errorString().toStdString().c_str());
        return false;
    }

    mRemoteAddress = QHostAddress(mUdpIP);
    return true;
}

bool UdpServerConnector::stopIO()
{
    if (mUdpSocket)
    {
        mUdpSocket->close();
    }
    else
    {
        LOG_DEBUG("mUdpSocket is null");
        return false;
    }

    if (mUdpSocket->isOpen())
    {
        return false;
    }

    return true;
}

void UdpServerConnector::send(const char* data2send, int length)
{
    //@todo
    QByteArray msg(data2send, length);

    if (mUdpSocket)
    {
        mUdpSocket->localAddress();
        mUdpSocket->writeDatagram(msg, mRemoteAddress, mRemotePort);
    }
}

void UdpServerConnector::send(std::string target, const char* data2send, int length)
{
    //@todo
    (void) target;
    (void) data2send;
    (void) length;
    return;
}

void UdpServerConnector::handleReadyRead()
{
    QByteArray data = mUdpSocket->readAll();
    emit IOConnector::handleIOMessage(data.data(), data.size());
}

