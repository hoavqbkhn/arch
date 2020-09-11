#ifndef UDPSERVERCONNECTOR_H
#define UDPSERVERCONNECTOR_H
#include <QObject>
#include "ioconnector.h"
#include <QUdpSocket>
#include <QSharedPointer>
#include "logger/logger.h"


/**
     * @brief The UdpServerConnector class
     * Handle Udp connection
     */
class UdpServerConnector : public IOConnector
{
        Q_OBJECT
    public:
        UdpServerConnector(const std::string& udpIP, int localPort, int remotePort = 0);
        ~UdpServerConnector();

        bool startIO() override;

        bool stopIO() override;

        void send(const char* data2send, int length) override;

        void send(std::string target, const char* data2send, int length) override;

    public slots:
        void handleReadyRead();
    private:
        QHostAddress mRemoteAddress;
        QString mUdpIP;
        int mLocalPort;
        int mRemotePort;
        QSharedPointer<QUdpSocket> mUdpSocket {nullptr};

};




#endif // UDPSERVERCONNECTOR_H
