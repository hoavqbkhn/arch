/*
 * File:   processormanager.h
 * Author: sangnv17@viettel.com.vn
 *
 * Created on December 1, 2019, 6:00 PM
 */

#ifndef SERVICEMANAGER_H
#define SERVICEMANAGER_H

#include <QMap>
#include "processorabstract.h"


/**
     * @brief The ProcessorManager class
     * This class for handleing message bus in the whole system
     */
class ProcessorManager : public QObject
{
        Q_OBJECT
    public:
        static ProcessorManager* getInstance();
        ~ProcessorManager();
        /**
         * @brief registerProcessor
         * @param processor
         * @return
         * register processor to messages bus
         */
        bool registerProcessor(ProcessorAbstract* processor);

        /**
         * @brief deregisterProcessor
         * @param processorName
         * @return
         * deregister processor to messages bus
         */
        bool deregisterProcessor(QString processorName);
        /**
         * @brief publish
         * @param msg
         * @param processorName
         * @return
         * send msg to specified processor
         */
        bool publish(std::shared_ptr<InnerMessage> msg, QString processorName);

    private:
        ProcessorManager();
        static ProcessorManager self;
        QMap<QString, ProcessorAbstract*> mMapProcessor;
};


#endif // SERVICEMANAGER_H
