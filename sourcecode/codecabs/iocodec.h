#ifndef IOCODEC_H
#define IOCODEC_H

#include <memory>
#include "messageabs/innermessage.h"
#include "messageabs/iorawmessage.h"
#include "helper/bytebuffer.h"


/**
     * @brief The IOCodec class
     * Abstract class for decoding and encoding handler
     */
class IOCodec
{
    public:
        IOCodec();
        IOCodec(std::string name);
        virtual ~IOCodec();

        /**
         * @brief decode raw data from io
         * @param data : data
         * @param length : length of data
         * @return InnerMessage
         */
        virtual std::shared_ptr<InnerMessage> decode(const char* data, int length) = 0;

        /**
         * @brief encode data to send to io
         * @param msg
         * @return raw data
         */
        virtual std::shared_ptr<IORawMessage> encode(std::shared_ptr<InnerMessage> msg) = 0;
    private:
        std::string mName;
};



#endif // IOCODEC_H
