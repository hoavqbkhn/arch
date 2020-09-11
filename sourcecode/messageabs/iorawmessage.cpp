#include "messageabs/iorawmessage.h"
#include "logger/logger.h"


IORawMessage::IORawMessage(const char* data, unsigned int length)
{
    mLength = length;
    mpData = new char[mLength];
    memcpy(mpData, data, mLength);
}

IORawMessage::~IORawMessage()
{
    if (mpData)
    {
        delete[] mpData;
    }
}

std::string IORawMessage::toString()
{
    return "RawMessage: TODO hexa presentation";
}

unsigned int IORawMessage::getLength() const
{
    return mLength;
}

char* IORawMessage::getData() const
{
    return mpData;
}

