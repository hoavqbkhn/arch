#include "processorabstract.h"
#include "processormanager.h"
#include <sys/syscall.h>
#include <unistd.h>


ProcessorAbstract::ProcessorAbstract(const QString& processorName)
    : mProcessorName(processorName)
{
    //Register processor
    ProcessorManager::getInstance()->registerProcessor(this);
    //    LOG_DEBUG("[%s] Threadid = %s", mServiceName.toStdString().c_str(), QThread::currentThreadId());
    mThread = QSharedPointer<WorkerThread>(new WorkerThread());
    this->moveToThread(mThread.data());
    QObject::connect(mThread.data(), &QThread::finished, this, &ProcessorAbstract::deleteLater);
    mThread->start(QThread::Priority::NormalPriority);
    connect(this, &ProcessorAbstract::sendMessage, this, &ProcessorAbstract::onMessage, Qt::QueuedConnection);
    connect(this, &ProcessorAbstract::startProcess, this, &ProcessorAbstract::onStartProcess, Qt::QueuedConnection);
    connect(this, &ProcessorAbstract::stopProcess, this, &ProcessorAbstract::onStopProcess, Qt::BlockingQueuedConnection);
}

ProcessorAbstract::~ProcessorAbstract()
{
    LOG_DEBUG("[%s] Destructor", mProcessorName.toStdString().c_str());
    ProcessorManager::getInstance()->deregisterProcessor(this->getProcessorName());
    mThread->quit();
    mThread->wait();
}

QString ProcessorAbstract::getProcessorName() const
{
    return mProcessorName;
}

bool ProcessorAbstract::publish(std::shared_ptr<InnerMessage> msg, const QString& processorName)
{
    if (msg == nullptr)
    {
        LOG_DEBUG("Publish a null message!!");
        return false;
    }
    else
    {
        ProcessorManager::getInstance()->publish(msg, processorName);
    }

    return true;
}

void ProcessorAbstract::onStartProcess()
{
    LOG_DEBUG("Start process %s - LWP = %ld", getProcessorName().toStdString().c_str(), syscall(SYS_gettid));
}

void ProcessorAbstract::onStopProcess()
{
    LOG_DEBUG("Stop process %s - LWP = %ld", getProcessorName().toStdString().c_str(), syscall(SYS_gettid));
}

