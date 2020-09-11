#include "tcpclientconnector.h"


TcpClientConnector::TcpClientConnector(const std::string& ip, int port, bool autocon, unsigned int maxTryReconn, unsigned int intervalReconn)
    : mTcpIP(QString::fromStdString(ip)), mLocalPort(port), mMaxTryReconnect(maxTryReconn), mIsAutoReconnect(autocon), mIntervalReconnect(intervalReconn)
{
}

TcpClientConnector::~TcpClientConnector()
{
}

bool TcpClientConnector::startIO()
{
    //    LOG_DEBUG("startIO Threadid TcpClientConnector = %s", QThread::currentThreadId());
    if (!mTcpSocket)
    {
        mTcpSocket = QSharedPointer<QTcpSocket>(new QTcpSocket());
        connect(mTcpSocket.data(), &QTcpSocket::readyRead, this, &TcpClientConnector::handleReadyRead);
        connect(mTcpSocket.data(), &QTcpSocket::stateChanged, this, &TcpClientConnector::hanleState);
    }

    if (!mTimerReconnect)
    {
        mTimerReconnect = QSharedPointer<QTimer>(new QTimer());
        connect(mTimerReconnect.data(), &QTimer::timeout, this, &TcpClientConnector::startIO);
    }

    if (mTcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        LOG_DEBUG("[ConectorId %d] Start connect when is connected", getUID());
        mTimerReconnect->stop();
        return true;
    }

    if (mCounterReconnect > mMaxTryReconnect)
    {
        LOG_DEBUG("[ConectorId %d] mCounterReconnect > mMaxTryReconnect", getUID());
        mTimerReconnect->stop();
        return false;
    }

    if (mTcpSocket->state() == QAbstractSocket::UnconnectedState)
    {
        LOG_DEBUG("[ConectorId %d] Start connect to Host %s, port %d", getUID(), mTcpIP.toStdString(), mLocalPort);
        mTcpSocket->connectToHost(mTcpIP, mLocalPort);
        mCounterReconnect++;
    }

    if (mTcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        //connect ok
        return true;
    }
    else
    {
        //start timer reconnect
        mTimerReconnect->start(mIntervalReconnect);
    }

    return false;
}

bool TcpClientConnector::stopIO()
{
    //    LOG_DEBUG("stopIO Threadid TcpClientConnector = %s", QThread::currentThreadId());
    mIsAutoReconnect = false;

    if (mTimerReconnect && mTimerReconnect->isActive())
    {
        LOG_DEBUG("[ConectorId %d] Stop TimerReconnect", getUID());
        mTimerReconnect->stop();
    }

    if (mTcpSocket)
    {
        if (mTcpSocket->state() != QAbstractSocket::UnconnectedState)
        {
            mTcpSocket->disconnectFromHost();
            mTcpSocket->waitForDisconnected();
        }

        mTcpSocket->close();
    }
    else
    {
        LOG_DEBUG("[ConectorId %d] mTcpSocket is null", getUID());
    }

    if (mTcpSocket->isOpen())
    {
        return false;
    }

    return true;
}

void TcpClientConnector::send(const char* data2send, int length)
{
    qint64 r = mTcpSocket->write(data2send,length);
    LOG_DEBUG("[ConectorId %d] socket write %d bytes in total %d", getUID(),r, length);
}

void TcpClientConnector::send(std::string target, const char* data2send, int length)
{
    (void)data2send;
    (void) target;
    (void)length;
    LOG_ERROR("Unsupport function");
}

void TcpClientConnector::handleReadyRead()
{
    QByteArray data = mTcpSocket->readAll();
    emit IOConnector::handleIOMessage(data.data(), data.size());
}

void TcpClientConnector::onSocketClosed()
{
    if (mTcpSocket)
    {
        mTcpSocket->close();
    }

    setIsConnected(false);

    if (mTimerReconnect && mIsAutoReconnect)
    {
        if (!mTimerReconnect->isActive())
        {
            LOG_DEBUG("[ConectorId %d] Start timer reconnect TCP socket", getUID());
            mTimerReconnect->start(mIntervalReconnect);
        }
        else
        {
            LOG_DEBUG("[ConectorId %d] Timer Reconnect is Active", getUID());
        }
    }
}

void TcpClientConnector::onSocketConnected()
{
    setIsConnected(true);
    LOG_DEBUG("[ConectorId %d] Socket is connected", getUID());
    mCounterReconnect = 0;

    if (mTimerReconnect)
    {
        if (mTimerReconnect->isActive())
        {
            mTimerReconnect->stop();
        }
    }
}



void TcpClientConnector::hanleState(QAbstractSocket::SocketState state)
{
    switch (state)
    {
        case QAbstractSocket::SocketState::ConnectedState:
            LOG_DEBUG("[ConectorId %d] Change socket state to ConnectedState", getUID());
            onSocketConnected();
            break;

        case QAbstractSocket::SocketState::UnconnectedState:
            LOG_DEBUG("[ConectorId %d] Change socket state to UnconnectedState", getUID());
            onSocketClosed();
            break;

        default:
            break;
    }
}
