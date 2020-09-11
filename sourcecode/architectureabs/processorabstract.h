/*
 * File:   processorabstract.h
 * Author: sangnv17@viettel.com.vn
 *
 * Created on December 1, 2019, 6:00 PM
 */
#ifndef SERVICEABSTRACT_H
#define SERVICEABSTRACT_H

#include <QObject>
#include <QSharedPointer>
#include <memory>
#include "messageabs/innermessage.h"
#include "workerthread.h"
#include "logger/logger.h"
#include <QTimer>
#include <QVector>
#include <QSharedPointer>


/**
     * @brief ProcessorAbstract
     * @param processorName
     * abstract class for all processor
     */
class ProcessorAbstract: public QObject
{
        Q_OBJECT
    public:


        ProcessorAbstract(const QString& processorName);
        virtual ~ProcessorAbstract();
        QString getProcessorName() const;

        /**
         * @brief send message "msg" to processor having name "processorName"
         * @param msg: msg to publish
         * @param processorName: processor to publish to
         * @return
         */
        bool publish(std::shared_ptr<InnerMessage> msg, const QString& processorName);

    signals:
        /**
         * @brief sendMessage: send message to this processor
         * @param msg
         */
        void sendMessage(std::shared_ptr<InnerMessage> msg);

        /**
         * @brief startProcess: this signal connected to onStartProcess() then we can call onStartProcess()
         * from another thread
         */
        void startProcess();
        /**
         * @brief stopProcess: this signal connected to onStopProcess() then we can call onStopProcess()
         * from another thread
         */
        void stopProcess();
    public slots:
        /**
         * @brief onMessage :solve all messages from other processors
         * @param msg
         */
        virtual void onMessage(std::shared_ptr<InnerMessage> msg) = 0;

        /**
         * @brief onStartProcess
         * start this processor and allocate resourcers of this class in this processor's thread
         */
        virtual void onStartProcess();
        /**
         * @brief onStopProcess
         * stop this processor and free resourcers of this class in this processor's thread
         */
        virtual void onStopProcess();

    private:
        ProcessorAbstract(const ProcessorAbstract&) = delete;
        ProcessorAbstract(ProcessorAbstract&&) = delete;
        ProcessorAbstract& operator=(const ProcessorAbstract&) = delete;
        ProcessorAbstract& operator=(ProcessorAbstract &&) = delete;

    private:
        QString mProcessorName;
        QSharedPointer<WorkerThread> mThread;
        QVector<QSharedPointer<QTimer>> mTimerVector;

};



#endif // SERVICEABSTRACT_H
