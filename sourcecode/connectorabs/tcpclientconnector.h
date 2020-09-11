#ifndef TCPCLIENTCONNECTOR_H
#define TCPCLIENTCONNECTOR_H
#include <QObject>
#include "ioconnector.h"
#include <QTcpSocket>
#include <QSharedPointer>
#include "logger/logger.h"
#include <QTimer>
#include <QThread>
#include "commondef.h"

/**
     * @brief The TcpClientConnector class
     * Handle tcp connection
     */
class TcpClientConnector : public IOConnector
{
        Q_OBJECT
    public:
        TcpClientConnector(const std::string& ip, int port, bool autocon = true, unsigned int maxTryReconn = UINT_MAX, unsigned int intervalReconn = TIME_INTERVAL_RECONNECT);
        ~TcpClientConnector();


        bool stopIO() override;

        void send(const char* data2send, int length) override;

        void send(std::string target, const char* data2send, int length) override;


    public slots:
        bool startIO() override;
        void handleReadyRead();
        void onSocketClosed();
        void onSocketConnected();
        void hanleState(QAbstractSocket::SocketState state);
    private:
        QString mTcpIP;
        int mLocalPort {0};
        unsigned int mMaxTryReconnect {UINT_MAX};
        bool mIsAutoReconnect {false};
        unsigned int mIntervalReconnect {0};
        unsigned int mCounterReconnect {0};
        QSharedPointer<QTimer> mTimerReconnect {nullptr};
        QSharedPointer<QTcpSocket> mTcpSocket {nullptr};

};

#endif // TCPCLIENTCONNECTOR_H
