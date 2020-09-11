/*
 * File:   multiioprocessor.h
 * Author: sangnv17@viettel.com.vn
 *
 * Created on December 1, 2019, 6:00 PM
 */

#ifndef MULTIIOPROCESSOR_H
#define MULTIIOPROCESSOR_H

#include "processorabstract.h"
#include "connectorabs/ioconnector.h"
#include "codecabs/iocodec.h"

/**
 * this class abstract for object having multi ioconnector
 */

/**
     * @brief The MultiIOProcessor class
     * this class abstract for object having multi ioconnector
     */
class MultiIOProcessor: public ProcessorAbstract
{
        Q_OBJECT
    public:

        MultiIOProcessor(const QString& processorName,
                         std::shared_ptr<IOCodec> codec,
                         std::list<std::shared_ptr<IOConnector>> connectors);
        virtual ~MultiIOProcessor();

        /**
         * @brief onStartProcess: start io
         */
        void onStartProcess() override;

        /**
         * @brief onStopProcess: stop io
         */
        void onStopProcess() override;

        /**
         * @brief sending function to all io connector
         * @param msg
         * @return
         */
        virtual bool send(const std::shared_ptr<InnerMessage>& msg);

        /**
         * @brief sending function to specified io connector
         * @param msg
         * @param connectorID
         * @return
         */
        virtual bool send(std::shared_ptr<InnerMessage> msg, unsigned int connectorID);

        /**
         * @brief processIOMessage
         * @param msg
         * solve data and send to processor
         */
        virtual void processIOMessage(const std::shared_ptr<InnerMessage>& msg) = 0;

        std::shared_ptr<IOConnector> getConnector(unsigned int connectorId);

        void setListConnector(const std::list<std::shared_ptr<IOConnector> >& listConnector);

    public slots:
        /**
         * @brief onHandleIOMessage: handle data from io
         * @param data
         * @param length
         */
        void onHandleIOMessage(const char* data, int length);


        /**
         * @brief onHandleIOError
         * Handle all errors relate to IO connector
         * such as serial error, electric error
         * @param msg
         * Error is encapsulated to InnerMessage
         */
        virtual void onHandleIOError(std::shared_ptr<InnerMessage> msg);

        /**
         * @brief onHandleIOClosed
         */
        virtual void onHandleIOClosed();

    private:
        std::shared_ptr<IOCodec> mCodec;
        std::list<std::shared_ptr<IOConnector>> mListConnector;
};



#endif // MULTIIOPROCESSOR_H
