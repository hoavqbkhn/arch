#ifndef FAILTOLERANCEIOPROCESSOR_H
#define FAILTOLERANCEIOPROCESSOR_H

#include <QTimer>
#include <QSharedPointer>
#include "multiioprocessor.h"


class FailToleranceIOProcessor: public MultiIOProcessor
{
        Q_OBJECT
    public:
        FailToleranceIOProcessor(const QString& processorName,
                                 std::shared_ptr<IOCodec> codec,
                                 std::shared_ptr<IOConnector> mainConnector,
                                 std::shared_ptr<IOConnector> alterConnector);
        virtual ~FailToleranceIOProcessor();

        virtual void onStartProcess() override;

        virtual void onStopProcess() override;

        std::shared_ptr<IOConnector> getMainConnector();

        std::shared_ptr<IOConnector> getAlterConnector();
    public slots:
        /**
        * check main connector
        * if smt wrong, swith to alter
        */
        virtual void checkConnectorsState();

    private:
        unsigned int mConnectorMainID;
        unsigned int mConnectorAlterID;
        QSharedPointer<QTimer> mTimerCheckConnectorsState;
        const int INTERVAL_CHECK_CONNECTORS_STATE = 100;
};



#endif // FAILTOLERANCEIOPROCESSOR_H
