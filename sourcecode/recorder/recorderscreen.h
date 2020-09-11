#ifndef RECORDERSCREEN_H
#define RECORDERSCREEN_H

#include <QObject>
#include "gst/gst.h"
#include <gst/app/gstappsink.h>
#include <gst/app/gstappsrc.h>
#include "logger/logger.h"
#include <sstream>

class RecorderScreen
{
    public:
        RecorderScreen();
        ~RecorderScreen();
        /**
         * @brief initPipelineStream
         */
        void initPipelineStream();
        /**
         * @brief processIni
         * init PipeLine stream and init loger
         */

        void processInit();
        /**
         * @brief initLogger
         */

        void initLogger();
        /**
         * @brief stopRecord
         */
        void stopRecord();
        /**
         * @brief startRecord
         */
        void startRecord();
        /**
         * @brief saveVideoToDatabase
         */
        QString getPathDirectory() const;
        /**
         * @brief saveVideoToDatabase
         */
    private:
        GstElement* mPipeline {nullptr};
        GstBus* mGstBus {nullptr};
        GstMessage* mGstMsg {nullptr};
        QString mVideoPathName;

    private:
        RecorderScreen& operator = (const RecorderScreen&) = delete;

};

#endif // RECORDERSCREEN_H
