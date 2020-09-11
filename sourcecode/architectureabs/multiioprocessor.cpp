#include "multiioprocessor.h"


MultiIOProcessor::MultiIOProcessor(const QString& processorName,
                                   std::shared_ptr<IOCodec> codec,
                                   std::list<std::shared_ptr<IOConnector>> connectors)
    : ProcessorAbstract(processorName), mCodec(codec)
{
    std::copy(connectors.begin(), connectors.end(), std::back_inserter(mListConnector));

    //Connect connector signal and processor slot
    for (auto conn : mListConnector)
    {
        QObject::connect(conn.get(), &IOConnector::handleIOMessage, this, &MultiIOProcessor::onHandleIOMessage, Qt::AutoConnection);
        QObject::connect(conn.get(), &IOConnector::handleIOError, this, &MultiIOProcessor::onHandleIOError, Qt::AutoConnection);
        QObject::connect(conn.get(), &IOConnector::connectorClosed, this, &MultiIOProcessor::onHandleIOClosed, Qt::AutoConnection);
        conn->moveToThread(this->thread());
    }
}

MultiIOProcessor::~MultiIOProcessor()
{
}

void MultiIOProcessor::onStartProcess()
{
    ProcessorAbstract::onStartProcess();

    for (auto conn : mListConnector)
    {
        if (!conn || !conn->startIO())
        {
            LOG_ERROR("[%s] Could not start IO", getProcessorName().toStdString().c_str());
        }
    }
}

void MultiIOProcessor::onStopProcess()
{
    for (auto conn : mListConnector)
    {
        if (!conn || !conn->stopIO())
        {
            LOG_ERROR("[%s] Could not stop IO", getProcessorName().toStdString().c_str());
        }
    }

    ProcessorAbstract::onStopProcess();
}

bool MultiIOProcessor::send(const std::shared_ptr<InnerMessage>& msg)
{
    auto outMsg = mCodec->encode(msg);

    for (auto conn : mListConnector)
    {
        if (conn && conn->isStatusActive() && conn->isConnected())
        {
            //only send in active IO
            if (outMsg != NULL)
            {
                conn->send(outMsg->getData(), outMsg->getLength());
            }
            else
            {
                LOG_ERROR("NULL DATA!");
                return false;
            }
        }
    }

    return true;
}

bool MultiIOProcessor::send(std::shared_ptr<InnerMessage> msg, unsigned int connectorID)
{
    auto encodedMsg = mCodec->encode(msg);

    if (encodedMsg)
    {
        auto conn = getConnector(connectorID);

        if (conn != nullptr && conn->isStatusActive() && conn->isConnected())
        {
            conn->send(encodedMsg->getData(), encodedMsg->getLength());
        }
        else
        {
            LOG_ERROR("Connector is NULL or inactive or not connected!");
            return false;
        }

        return true;
    }
    else
    {
        LOG_ERROR("Could not encode message");
    }

    return false;
}

std::shared_ptr<IOConnector> MultiIOProcessor::getConnector(unsigned int connectorId)
{
    for (auto conn : mListConnector)
    {
        if (conn->getUID() == connectorId)
        {
            return conn;
        }
    }

    return nullptr;
}

void MultiIOProcessor::onHandleIOMessage(const char* data, int length)
{
    auto decodedMsg = mCodec->decode(data, length);

    if (decodedMsg)
    {
        processIOMessage(decodedMsg);
    }
}

void MultiIOProcessor::onHandleIOError(std::shared_ptr<InnerMessage> msg)
{
    (void) msg;
}

void MultiIOProcessor::onHandleIOClosed()
{
}

void MultiIOProcessor::setListConnector(const std::list<std::shared_ptr<IOConnector> >& listConnector)
{
    mListConnector.clear();
    std::copy(listConnector.begin(), listConnector.end(), std::back_inserter(mListConnector));

    //Connect connector signal and processor slot
    for (auto conn : mListConnector)
    {
        QObject::connect(conn.get(), &IOConnector::handleIOMessage, this, &MultiIOProcessor::onHandleIOMessage, Qt::DirectConnection);
        QObject::connect(conn.get(), &IOConnector::handleIOError, this, &MultiIOProcessor::onHandleIOError, Qt::DirectConnection);
        conn->moveToThread(this->thread());
    }
}

