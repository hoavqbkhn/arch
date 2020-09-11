#ifndef NATSCONNECTOR_H
#define NATSCONNECTOR_H

#include <QObject>
#include "ioconnector.h"
#include "nats/nats.h"
#include <QTimer>
#include <QSharedPointer>
#include <QThread>



/**
     * @brief The NatsConnector class
     * Hanlde Nats connection
     */
class NatsConnector: public IOConnector
{
        Q_OBJECT
    public:
        NatsConnector(std::vector<std::string> topicListen,
                      std::string topicSend,
                      std::vector<std::string> listServerNatsCluster,
                      std::string cafile,
                      std::string key,
                      std::string cert);
        ~NatsConnector();

        bool startIO() override;

        bool stopIO() override;

        void send(const char* data2send, int length) override;

        void send(std::string target, const char* data2send, int length) override;

        std::string getCurrentConnectedUrl() const;
        void setCurrentConnectedUrl(const std::string& currentConnectedUrl);

    signals:
        //TODO: define a signal to emit data to processor
    private:


        natsConnection* mpConnection;
        natsSubscription* mpSubscription;
        natsStatus mNatsStatus;
        natsOptions* mpNatsOpts;
        volatile bool mIsDone;

        std::vector<std::string> mTopicListen;
        std::string mTopicSend;
        std::vector<std::string> mServerNats;
        std::string mCaFile;
        std::string mKeyFile;
        std::string mCertFile;
        std::string mCurrentConnectedUrl;
        QSharedPointer<QTimer> mTimerReconnect ;
        const int TIME_RECONNECT_WAIT_NATS = 1000; //1s
        unsigned int mMaxTryReconnect {UINT_MAX};

};



#endif // NATSCONNECTOR_H
