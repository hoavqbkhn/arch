#include "failtoleranceioprocessor.h"



FailToleranceIOProcessor::FailToleranceIOProcessor(const QString& processorName,
                                                   std::shared_ptr<IOCodec> codec,
                                                   std::shared_ptr<IOConnector> mainConnector,
                                                   std::shared_ptr<IOConnector> alterConnector)
    : MultiIOProcessor(processorName,
                       codec,
                       std::list<std::shared_ptr<IOConnector>> {mainConnector, alterConnector})
{
    if (mainConnector)
    {
        mConnectorMainID = mainConnector->getUID();
        mainConnector->setStatusActive(true);
    }

    if (alterConnector)
    {
        mConnectorAlterID = alterConnector->getUID();
        alterConnector->setStatusActive(false);
    }
}

FailToleranceIOProcessor::~FailToleranceIOProcessor()
{
}

void FailToleranceIOProcessor::onStartProcess()
{
    // Do start parent's process
    MultiIOProcessor::onStartProcess();
    // Start timers in process's thread
    mTimerCheckConnectorsState = QSharedPointer<QTimer>(new QTimer());
    QObject::connect(mTimerCheckConnectorsState.data(), &QTimer::timeout, this, &FailToleranceIOProcessor::checkConnectorsState);
    mTimerCheckConnectorsState->start(INTERVAL_CHECK_CONNECTORS_STATE);
}

void FailToleranceIOProcessor::onStopProcess()
{
    // Stop timers in process's thread
    if (mTimerCheckConnectorsState && mTimerCheckConnectorsState->isActive())
    {
        mTimerCheckConnectorsState->stop();
    }

    // Do stop parent's process
    MultiIOProcessor::onStopProcess();
}

std::shared_ptr<IOConnector> FailToleranceIOProcessor::getMainConnector()
{
    return getConnector(mConnectorMainID);
}

std::shared_ptr<IOConnector> FailToleranceIOProcessor::getAlterConnector()
{
    return getConnector(mConnectorAlterID) ;
}

void FailToleranceIOProcessor::checkConnectorsState()
{
    //check main connector is active and connected yet?
    //if not -> check alter connector
    //if ok -> swap main = alter, alter = main
    if (!getMainConnector() || !getAlterConnector())
    {
        LOG_ERROR("Main or alter connector is null");
        return;
    }

    //                        LOG_DEBUG("checkConnectorsState main[%d][%s]-isconnected[%d] alter[%d][%s]-isconnected[%d]",
    //                                getMainConnector()->getUID(),getMainConnector()->getIOTypeName().c_str(),getMainConnector()->isConnected(),
    //                                getAlterConnector()->getUID(),getAlterConnector()->getIOTypeName().c_str(),getAlterConnector()->isConnected());
    if (!getMainConnector()->isConnected() && getAlterConnector()->isConnected())
    {
        getMainConnector()->setStatusActive(false);
        getAlterConnector()->setStatusActive(true);
        unsigned int tmp = mConnectorMainID;
        mConnectorMainID = mConnectorAlterID;
        mConnectorAlterID = tmp;
    }
}

