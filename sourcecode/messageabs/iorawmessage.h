#ifndef IORAWMESSAGE_H
#define IORAWMESSAGE_H

#include "innermessage.h"


class IORawMessage: public InnerMessage
{
    public:
        IORawMessage(const char* data, unsigned int length);
        virtual ~IORawMessage();

        virtual std::string toString() override;
        unsigned int getLength() const;


        char* getData() const;

    private:
        unsigned int mLength;
        char* mpData;
        unsigned int mConnectorID;
};

#endif // IORAWMESSAGE_H
