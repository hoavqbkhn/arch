#include "ioconnector.h"
#include "commondef.h"

IOConnector::IOConnector()
{
    mUID = APPLICATION_ID++;
}

IOConnector::~IOConnector()
{
}

void IOConnector::onConnected()
{
    setIsConnected(true);
}

void IOConnector::onDisconnected()
{
    setIsConnected(false);
}

void IOConnector::setIsConnected(bool state)
{
    mStatusConnect = state;
}

bool IOConnector::isConnected()
{
    return mStatusConnect;
}

void IOConnector::setStatusActive(bool statusActive)
{
    this->mStatusActive = statusActive;
}

bool IOConnector::isStatusActive() const
{
    return mStatusActive;
}

bool IOConnector::setUID(unsigned int id)
{
    if (APPLICATION_ID >= id)
    {
        return false;
    }
    else
    {
        APPLICATION_ID = id;
        mUID = id;
        return true;
    }
}

unsigned int IOConnector::getUID() const
{
    return mUID;
}

std::string IOConnector::getConnectorName() const
{
    return mConnectorName;
}

void IOConnector::setConnectorName(const std::string& connectorName)
{
    mConnectorName = connectorName;
}


