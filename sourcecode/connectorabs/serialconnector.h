#ifndef SERIALCONNECTOR_H
#define SERIALCONNECTOR_H

#include <QObject>
#include <QSharedPointer>
#include <QtSerialPort/QSerialPort>
#include "ioconnector.h"


/**
     * @brief The SerialConnector class
     * Handle Serial connection
     */
class SerialConnector: public IOConnector
{
        Q_OBJECT
    public:
        SerialConnector(const std::string& portName,
                        qint32 baudrate);
        ~SerialConnector();

        bool startIO() override;

        bool stopIO() override;

        void send(const char* data2send, int length) override;

        void send(std::string target, const char* data2send, int length) override;

        void setParity(const QSerialPort::Parity& parity);

        void setStopBits(const QSerialPort::StopBits& stopBits);

        void setDataBits(const QSerialPort::DataBits& dataBits);

        void setFlowControl(const QSerialPort::FlowControl& flowControl);

    public slots:
        void handleReadyRead();
    private:
        QSharedPointer<QSerialPort> mSerialPort {nullptr};
        std::string mPortName;
        qint32 mBaudRate;
        QSerialPort::Parity mParity {QSerialPort::NoParity};
        QSerialPort::StopBits mStopBits {QSerialPort::OneStop};
        QSerialPort::DataBits mDataBits {QSerialPort::Data8};
        QSerialPort::FlowControl mFlowControl {QSerialPort::NoFlowControl};


};


#endif // SERIALCONNECTOR_H
