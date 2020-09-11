#include "singleioprocessor.h"


SingleIOProcessor::SingleIOProcessor(const QString& processorName,
                                     std::shared_ptr<IOCodec> codec,
                                     std::shared_ptr<IOConnector> connector)
    : MultiIOProcessor(processorName, codec, std::list<std::shared_ptr<IOConnector>> {connector})
{
    mConnectorID = connector->getUID();
}

SingleIOProcessor::~SingleIOProcessor()
{
}

void SingleIOProcessor::updateConnector(std::shared_ptr<IOConnector> newConn)
{
    mConnectorID = newConn->getUID();
    setListConnector(std::list<std::shared_ptr<IOConnector>> {newConn});
}

std::shared_ptr<IOConnector> SingleIOProcessor::getThisConnector()
{
    return getConnector(mConnectorID);
}

