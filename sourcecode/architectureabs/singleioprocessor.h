/*
 * File:   singleioprocessor.h
 * Author: sangnv17@viettel.com.vn
 *
 * Created on December 1, 2019, 6:00 PM
 */
#ifndef SINGLEIOPROCESSOR_H
#define SINGLEIOPROCESSOR_H
#include "multiioprocessor.h"


/**
     * @brief The SingleIOProcessor class
     * this class for object having only one io connector
     */
class SingleIOProcessor: public MultiIOProcessor
{
    public:
        SingleIOProcessor(const QString& processorName,
                          std::shared_ptr<IOCodec> codec,
                          std::shared_ptr<IOConnector> connector);
        virtual ~SingleIOProcessor();
        /**
         * @brief updateConnector
         * to replace oldconnector by a newconnector
         */
        void updateConnector(std::shared_ptr<IOConnector> newConn);

        std::shared_ptr<IOConnector> getThisConnector();
    private:
        unsigned int mConnectorID;
};




#endif // SINGLEIOPROCESSOR_H
