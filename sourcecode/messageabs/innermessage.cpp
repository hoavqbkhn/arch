#include "messageabs/innermessage.h"


InnerMessage::InnerMessage()
{
}

InnerMessage::~InnerMessage()
{
}

std::string InnerMessage::toString()
{
    return typeid(this).name();
}


