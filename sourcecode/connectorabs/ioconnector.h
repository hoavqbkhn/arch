

#ifndef IOCONNECTOR_H
#define IOCONNECTOR_H

#include <QObject>
#include <memory>
#include <string>
#include "messageabs/innermessage.h"


/**
     * @brief The IOConnector class
     * Abstract class for connection handling object
     */
class IOConnector: public QObject
{
        Q_OBJECT
    public:
        IOConnector();
        virtual ~IOConnector();
        /**
         * @brief startIO
         * @return
         * start connecting io and allocate resources for connector
         */
        virtual bool startIO() = 0;

        /**
         * @brief stopIO
         * @return
         * stop connecting io and free resources for connector
         */
        virtual bool stopIO() = 0;

        /**
         * for sending unique target
         * ex: serial, tcp
         * if send to variable target, use send(target, message)
         * ex: udp, nats...
         * @param message
         */
        virtual void send(const char* data2send, int length) = 0;

        /**
         * for sending unique target
         * ex: serial, tcp
         * if send to variable target, use send(target, message)
         * ex: udp, nats...
         * @param message
         */
        virtual void send(std::string target, const char* data2send, int length) = 0;

        /**
         * @brief onConnected
         * update state of connection to connected
         */
        virtual void onConnected();

        /**
         * @brief onDisconnected
         * update state of connection to disconnected
         */
        virtual void onDisconnected();

        /**
         * @brief setIsConnected : set state of connection
         * @param state
         *
         */
        virtual void setIsConnected(bool state);
        /**
         * @brief isConnected
         * @return state of connection
         * true: connected
         * false: disconnected
         */
        virtual bool isConnected();

        void setStatusActive(bool statusActive);

        bool isStatusActive() const;

        bool setUID(unsigned int id);

        unsigned int getUID() const;

        std::string getConnectorName() const;
        void setConnectorName(const std::string& connectorName);

    signals:
        /**
         * @brief handleIOMessage : push data from io to processor
         * @param data
         * @param length
         */
        void handleIOMessage(const char* data, int length);

        /**
         * @brief handleIOError
         * report relative IO errors to processor
         * @param msg
         */
        void handleIOError(std::shared_ptr<InnerMessage> msg);

        /**
         * @brief onClosedConnector
         */
        void connectorClosed();

    private:
        unsigned int mUID;
        bool mStatusConnect {false};

        /**
        * active = true is default
        */
        bool mStatusActive {true};

        std::string mConnectorName;
};




#endif // IOCONNECTOR_H
