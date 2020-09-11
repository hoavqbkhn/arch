#ifndef INNERMESSAGE_H
#define INNERMESSAGE_H

#include <string>
#include <typeinfo>


class InnerMessage
{
    public:
        InnerMessage();
        virtual ~InnerMessage();
        virtual std::string toString();
};



#endif // INNERMESSAGE_H
