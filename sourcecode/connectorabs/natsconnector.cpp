#include "natsconnector.h"
#include "logger/logger.h"
#include "commondef.h"

/**
 * @brief onReconnectedNats
 * Handle event reconnected success on Nats
 * @param nc
 * @param closure
 */
static void onReconnectedNats(natsConnection* nc, void* closure);

/**
 * @brief onMessage
 * Handle event received message when using async subcribe
 * @param nc
 * @param sub
 * @param msg
 * @param closure
 */
static void onMessage(natsConnection* nc, natsSubscription* sub,
                      natsMsg* msg, void* closure);

/**
 * @brief onError
 * Handle event error on Nats
 * @param nc
 * @param subscription
 * @param err
 * @param closure
 */
static void onError(natsConnection* nc, natsSubscription* subscription,
                    natsStatus err, void* closure);
/**
 * @brief onDisconnectedNats
 * Handle event disconnected on Nats
 * @param nc
 * @param closure
 */
static void onDisconnectedNats(natsConnection* nc, void* closure);


/**
 * @brief onClosed
 * Hanle event closed on Nats
 * @param nc
 * @param closure
 */
static void onClosed(natsConnection* nc, void* closure);

NatsConnector::NatsConnector(std::vector<std::string> topicListen,
                             std::string topicSend,
                             std::vector<std::string> listServerNatsCluster,
                             std::string cafile,
                             std::string key,
                             std::string cert)
    : mTopicListen(topicListen), mTopicSend(topicSend), mServerNats(listServerNatsCluster), mCaFile(cafile), mKeyFile(key), mCertFile(cert)
{
}

NatsConnector::~NatsConnector()
{
}

bool NatsConnector::startIO()
{
    if (isConnected())
    {
        LOG_DEBUG("Connect start when connected");
        return false;
    }

    mNatsStatus = natsOptions_Create(&mpNatsOpts);

    if (mNatsStatus == NATS_OK)
    {
        natsOptions_SetReconnectWait(mpNatsOpts, TIME_RECONNECT_WAIT_NATS);
        natsOptions_SetMaxReconnect(mpNatsOpts, mMaxTryReconnect);
        natsOptions_SetSecure(mpNatsOpts, true);
        natsOptions_LoadCATrustedCertificates(mpNatsOpts, mCaFile.c_str());
        natsOptions_LoadCertificatesChain(mpNatsOpts, mCertFile.c_str(), mKeyFile.c_str());
        nats_PrintLastErrorStack(stderr);
    }
    else
    {
        LOG_ERROR("Cannot natsOptions_Create");
        return false;
    }

    if (mNatsStatus == NATS_OK)
    {
        mNatsStatus = natsOptions_SetErrorHandler(
                          mpNatsOpts, &onError, this);
        mNatsStatus = natsOptions_SetReconnectedCB(
                          mpNatsOpts, &onReconnectedNats, this);
        mNatsStatus = natsOptions_SetDisconnectedCB(
                          mpNatsOpts, &onDisconnectedNats, this);
        mNatsStatus = natsOptions_SetClosedCB(
                          mpNatsOpts, &onClosed, this);
    }
    else
    {
        LOG_ERROR("Cannot natsOptions_SetReconnectWait");
        //start timer reconnect
        return false;
    }

    const char* tem[mServerNats.size()];

    for (unsigned int i = 0; i < mServerNats.size(); i++)
    {
        tem[i] = mServerNats.at(i).c_str();
    }

    if (mNatsStatus == NATS_OK)
    {
        mNatsStatus = natsOptions_SetServers(mpNatsOpts, tem, mServerNats.size());
    }
    else
    {
        LOG_ERROR("Cannot natsOptions_SetCB");
        return false;
    }

    if (mNatsStatus == NATS_OK)
    {
        mNatsStatus  = natsConnection_Connect(&mpConnection, mpNatsOpts);
    }
    else
    {
        LOG_ERROR("Cannot natsOptions_SetServers");
        return false;
    }

    if (mNatsStatus == NATS_OK)
    {
        // Creates an asynchronous subscription on subject "foo".
        // When a message is sent on subject "foo", the callback
        // onMsg() will be invoked by the client library.
        // You can pass a closure as the last argument.
        for (unsigned int i = 0; i < mTopicListen.size(); i++)
        {
            LOG_INFO("Listening on subject = %s", mTopicListen.at(i).c_str());
            mNatsStatus = natsConnection_Subscribe(&mpSubscription,
                                                   mpConnection,
                                                   mTopicListen.at(i).c_str(),
                                                   onMessage,
                                                   this);
        }
    }
    else
    {
        LOG_ERROR("Cannot natsConnection_Connect");

        if (!mTimerReconnect)
        {
            mTimerReconnect = QSharedPointer<QTimer> (new QTimer());
            connect(mTimerReconnect.data(), &QTimer::timeout, this, [&]()
            {
                if (!isConnected())
                {
                    LOG_DEBUG("Call reconnect nats io");
                    startIO();
                }
                else
                {
                    LOG_DEBUG("Stop timer reconnect nats io");
                    mTimerReconnect->stop();
                }
            });
            mTimerReconnect->start(TIME_INTERVAL_RECONNECT);
        }

        return false;
    }

    // For maximum performance, set no limit on the number of pending messages.
    if (mNatsStatus == NATS_OK)
    {
        if (mTopicListen.size() > 0)
            mNatsStatus = natsSubscription_SetPendingLimits(
                              mpSubscription, -1, -1);
    }
    else
    {
        LOG_ERROR("Cannot natsConnection_Subscribe");
        return false;
    }

    if (mNatsStatus == NATS_OK)
    {
        onConnected();
        // Save current server url
        const int length = 1024;
        char serverUrl[length];
        natsConnection_GetConnectedUrl(mpConnection, serverUrl, length);
        mCurrentConnectedUrl.clear();
        mCurrentConnectedUrl.append(serverUrl);
        LOG_DEBUG("Connected to url = %s", mCurrentConnectedUrl.c_str());
    }
    else
    {
        LOG_ERROR("Cannot natsSubscription_SetPendingLimits");
        return false;
    }

    return true;
}

bool NatsConnector::stopIO()
{
    LOG_DEBUG("Threadid Nats = %s", QThread::currentThreadId());

    if (mTimerReconnect && mTimerReconnect->isActive())
    {
        mTimerReconnect->stop();
    }

    if (!isConnected())
    {
        LOG_DEBUG("Call stop when not connected?");
        return false;
    }

    natsConnection_Close(mpConnection);
    natsSubscription_Destroy(mpSubscription);
    natsConnection_Destroy(mpConnection);
    natsOptions_Destroy(mpNatsOpts);
    //    nats_Close();
    onDisconnected();
    return true;
}

void NatsConnector::send(const char* data2send, int length)
{
    if (data2send != NULL)
    {
        mNatsStatus = natsConnection_Publish(
                          mpConnection, mTopicSend.c_str(), data2send, length);

        if (mNatsStatus == NATS_OK)
        {
        }
        else
        {
            LOG_ERROR("Error on send to topic: %s - status: %d - %s", mTopicSend.c_str()
                      , mNatsStatus, natsStatus_GetText(mNatsStatus));
            nats_PrintLastErrorStack(stderr);
        }
    }
    else
    {
        LOG_ERROR("Encode fail! NULL data encoded");
    }
}

void NatsConnector::send(std::string target, const char* data2send, int length)
{
    (void) target;
    (void) data2send;
    (void) length;
}

std::string NatsConnector::getCurrentConnectedUrl() const
{
    return mCurrentConnectedUrl;
}

void NatsConnector::setCurrentConnectedUrl(const std::string& currentConnectedUrl)
{
    mCurrentConnectedUrl = currentConnectedUrl;
}

void onReconnectedNats(natsConnection* nc, void* closure)
{
    const int length = 1024;
    char serverUrl[length];
    natsConnection_GetConnectedUrl(nc, serverUrl, length);
    std::string currentConnectedUrl(serverUrl);
    ((NatsConnector*)(closure))->onConnected();
    ((NatsConnector*)(closure))->setCurrentConnectedUrl(currentConnectedUrl);
    LOG_ERROR("onReconnected on url = %s", serverUrl);
}

void onMessage(natsConnection* nc, natsSubscription* sub, natsMsg* msg, void* closure)
{
    (void) nc;
    (void) sub;

    if (NatsConnector* temp = (NatsConnector*)(closure))
    {
        emit temp->handleIOMessage(natsMsg_GetData(msg), natsMsg_GetDataLength(msg));
        // Need to destroy the message!
        natsMsg_Destroy(msg);
    }
}

void onError(natsConnection* nc, natsSubscription* subscription, natsStatus err, void* closure)
{
    (void) nc;
    (void) subscription;
    LOG_ERROR("onError on url = %s - Error handled: %d - %sn",
              ((NatsConnector*)(closure))->getCurrentConnectedUrl().c_str(),
              err,
              natsStatus_GetText(err));
    nats_PrintLastErrorStack(stderr);
    ((NatsConnector*)(closure))->onDisconnected();
}

void onDisconnectedNats(natsConnection* nc, void* closure)
{
    (void) nc;
    ((NatsConnector*)(closure))->onDisconnected();
    LOG_ERROR("onDisconnected on url = %s",
              ((NatsConnector*)(closure))->getCurrentConnectedUrl().c_str());
}

void onClosed(natsConnection* nc, void* closure)
{
    (void) nc;
    ((NatsConnector*)(closure))->onDisconnected();
    ((NatsConnector*)(closure))->connectorClosed();
    LOG_ERROR("onClosed on url = %s",
              ((NatsConnector*)(closure))->getCurrentConnectedUrl().c_str());
}
