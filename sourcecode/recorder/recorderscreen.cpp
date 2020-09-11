#include "recorderscreen.h"
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QDateTime>
/**
 * @brief RecorderScreen::RecorderScreen
 *
 */

RecorderScreen::RecorderScreen()
{
    this->processInit();
    this->startRecord();
}

RecorderScreen::~RecorderScreen()
{
    this->stopRecord();
}

void RecorderScreen::initPipelineStream()
{
    gst_init(nullptr, nullptr);
    std::string pipeLine;
    std::ostringstream ss;
    ss << "ximagesrc use-damage=0  ! video/x-raw,framerate=60/1 ! queue ! videoscale ! videoconvert !  x264enc tune=zerolatency bitrate=4096 speed-preset=superfast !  h264parse config-interval=-1 ! queue  ! matroskamux name=mux  ! queue !"
       "filesink location=" + mVideoPathName.toStdString();
    ss << " pulsesrc buffer-time=20000000 ! audio/x-raw,channels=2,rate=48000,format=F32LE,payload=96 ! queue ! audioconvert ! queue  ! mux.";
    pipeLine  = ss.str();
    GError* err = nullptr;
    mPipeline = gst_parse_launch(pipeLine.c_str(), &err);

    if (err != nullptr)
    {
        qDebug("gstreamer video receiver failed to create pipeline at %d - %s\n", __LINE__, __FILE__);
        qDebug(" (%s)\n", err->message);
        g_error_free(err);
        return;
    }

    GstPipeline* pipeline  = GST_PIPELINE(mPipeline);

    if (!pipeline)
    {
        qDebug("gstreamer video receiver failed to cast GstElement into GstPipeline at line %d - %s \n", __LINE__, __FILE__);
        return ;
    }
}

void RecorderScreen::processInit()
{
    // getThe video path
    mVideoPathName = getPathDirectory();
    // init pipelineStream
    this->initPipelineStream();
}

void RecorderScreen::stopRecord()
{
    GstStateChangeReturn ret;
    ret = gst_element_set_state(mPipeline, GST_STATE_NULL);

    if (ret == GST_STATE_CHANGE_FAILURE)
    {
        LOG_DEBUG("StopRecord :GST_Failed");
    }
    else if (ret == GST_STATE_CHANGE_SUCCESS)
    {
        LOG_DEBUG("StopRecord : Successed");
    }

    // unref object
    gst_object_unref(mPipeline);
    gst_object_unref(mGstBus);
}
void RecorderScreen::startRecord()
{
    GstStateChangeReturn ret;
    ret = gst_element_set_state(mPipeline, GST_STATE_PLAYING);

    if (ret == GST_STATE_CHANGE_FAILURE)
    {
        LOG_DEBUG("StartRecord : GST_Failed");
    }
    else if (ret == GST_STATE_CHANGE_SUCCESS)
    {
        LOG_DEBUG("StartRecord : Successed");
    }

    // wait Error or EOS
    mGstBus = gst_element_get_bus(mPipeline);
    mGstMsg = gst_bus_timed_pop_filtered(mGstBus, GST_CLOCK_DONE, GST_MESSAGE_ERROR);

    //Parse message
    if (mGstMsg != nullptr)
    {
        GError* err;
        gchar* debug_info;

        switch (GST_MESSAGE_TYPE(mGstMsg))
        {
            case GST_MESSAGE_ERROR:
                gst_message_parse_error(mGstMsg, &err, &debug_info);
                g_printerr("Error received from element %s: %s\n", GST_OBJECT_NAME(mGstMsg->src), err->message);
                g_printerr("Debugging information: %s\n", debug_info ? debug_info : "none");
                g_clear_error(&err);
                g_free(debug_info);
                break;

            case GST_MESSAGE_EOS:
                g_print("End-Of-Stream reached.\n");
                break;

            default:
                /* We should not reach here because we only asked for ERRORs and EOS */
                g_printerr("Unexpected message received.\n");
                break;
        }

        gst_message_unref(mGstMsg);
    }
}
QString RecorderScreen::getPathDirectory() const
{
    QDir dir;
    QDateTime dateTime;
    QString videoFilePathName;
    QString date =  dateTime.currentDateTime().date().toString("yyyy.MM.dd"); // To make date folder
    QString time = dateTime.currentDateTime().time().toString("hh:mm:ss"); // To make File name by time
    // Back to one folder to make videoRecord folder which is the same order with LOG folder
    dir.setCurrent("../");
    qDebug() << "Current path" << dir.currentPath();

    // make VideoRecord Folder
    if (dir.mkdir("VideoRecord"))
    {
        LOG_DEBUG("Created VideoRecord Folder");
    }
    else
    {
        LOG_DEBUG(" VideoRecord Folder is Existed");
    }

    // Set currentpath is dir.currentPath()/VideoRecord
    dir.setCurrent(dir.currentPath() + QString("/VideoRecord"));

    if (dir.mkdir(date))
    {
        LOG_DEBUG("Created Date Folder");
    }
    else
    {
        LOG_DEBUG("Date Folder is existed");
    }

    dir.setCurrent("/" + dir.currentPath() + "/" + date);
    // append mp4 to videoPathName
    videoFilePathName = dir.currentPath() +  "/" + time + ".mp4";
    return videoFilePathName;
}
