#include "VideoStreamer.h"
#include <QDateTime>
#include <filesystem>
#include <iostream>

namespace cat { namespace cam {

VideoStreamer::VideoStreamer()
    : m_videoCapture(cv::VideoCapture{})
    , m_currentFrame(cv::Mat{})
    , m_prevFrame(cv::Mat{})
    , m_refreshTime(0)
    , m_motionEnabled(false)
    , m_camEnabled(false)
    , m_recognized(false)
    , m_activeDevId(DEVICE::RPI_CAM)
    , m_averageFps(0.)
    , m_frameCounter(0)
    , m_devPath(QString{"/dev/video0"})
    , m_screenshotFolder(QString("./screenshots"))
{
    connect(&m_refreshTime, &QTimer::timeout, this, &VideoStreamer::streamVideo);
}

VideoStreamer::~VideoStreamer()
{
    closeVideoCamera();
}

void
VideoStreamer::streamVideo()
{
    m_videoCapture >> m_currentFrame;
    QImage img = QImage(m_currentFrame.data, m_currentFrame.cols,
                        m_currentFrame.rows, QImage::Format_RGB888).rgbSwapped();
    emit newImage(img);

    if (m_prevFrame.empty()) {
        m_videoCapture >> m_prevFrame;
        std::cout << "m_motionEnabled: " << m_motionEnabled << std::endl;
        return;
    }

    if (m_motionEnabled) {
        handleMotion();
    }
}

void VideoStreamer::toggleMotion(bool onoff)
{
    if (false == onoff) {
        m_motionEnabled = false;
    } else {
        m_motionEnabled = true;
    }
    emit motionEnabledChanged(m_motionEnabled);
}

void VideoStreamer::toggleDevice(bool onoff)
{
    if (DEVICE::RPI_CAM == onoff) {
        m_activeDevId = 0;
    } else {
        m_activeDevId = 1;
    }
    emit activeDevIdChanged(m_activeDevId);
}

void VideoStreamer::toggleConnection(bool onoff)
{
    if (false == onoff) {
        closeVideoCamera();
    } else {
        openVideoCamera();
    }
}

bool
VideoStreamer::checkFrame(const cv::Mat& frame, const cv::Mat& prevFrame, int threshold) const
{
    cv::Mat grayFrame;
    cv::Mat grayPrevFrame;
    cv::Mat diffFrame;
    cv::Mat thresholdFrame;
    bool result = false;

    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
    cv::cvtColor(prevFrame, grayPrevFrame, cv::COLOR_BGR2GRAY);
    cv::absdiff(grayFrame, grayPrevFrame, diffFrame);
    cv::threshold(diffFrame, thresholdFrame, 127, 1, cv::THRESH_BINARY);

    cv::imshow("thresh", thresholdFrame);

    if (cv::countNonZero(thresholdFrame) >= threshold) {
        result = true;
    }

    return result;
}

void
VideoStreamer::takeScreenshot()
{
    if(!m_camEnabled) {
        std::cerr << "open stream first before taking screenshot" << std::endl;
        return;
    }
    std::filesystem::create_directories(m_screenshotFolder.toStdString());

    if (m_currentFrame.empty()) {
        std::cerr << "Something is wrong with the webcam, could not get frame." << std::endl;
    } else {
        cv::Mat rotate_90;
        cv::Mat flip_horizontal;
        cv::rotate(m_currentFrame, rotate_90, cv::ROTATE_90_COUNTERCLOCKWISE);
        cv::flip(rotate_90, flip_horizontal, 1);
        std::string fileName = m_screenshotFolder.toStdString() + "/" + getTimestamp() + ".jpg";
        cv::imwrite(fileName, flip_horizontal);
    }
}

void
VideoStreamer::clearScreenshotFolder()
{
    uint32_t error = std::filesystem::remove_all(m_screenshotFolder.toStdString());
    std::cout << "Error: " << strerror(error) << std::endl;
}

void VideoStreamer::autoconnect()
{
    toggleMotion(true);
    toggleDevice(false);
    toggleConnection(true);
}

std::string
VideoStreamer::getTimestamp() const
{
    QDateTime now = QDateTime::currentDateTime();
    QString timestamp = now.toString(QLatin1String("ddMMyyyy-hhmmss"));
    return QString::fromLatin1("pic%1").arg(timestamp).toStdString();
}

std::string VideoStreamer::buildPipeline(int width, int height, int framerate, int displayWidth, int displayHeight) const
{
    std::stringstream stream{};
    stream << " libcamerasrc ! video/x-raw, "
           << " width=(int)" << std::to_string(width) << ","
           << " height=(int)" << std::to_string(height) << ","
           << " framerate=(fraction)" << std::to_string(framerate) << "/1 !"
           << " videoflip method=vertical-flip !"
           << " videoconvert ! videoscale ! video/x-raw,"
           << " width=(int)" << std::to_string(displayWidth) << ","
           << " height=(int)" << std::to_string(displayHeight) << " ! appsink";

    std::cout << "Using pipeline: \n\t" << stream.str() << "\n\n\n";
    return stream.str();
}

void
VideoStreamer::openVideoCamera()
{
    if(!m_camEnabled)
    {
        if(DEVICE::RPI_CAM == m_activeDevId) {
            m_videoCapture.open(buildPipeline(CAPTURE_WIDTH, CAPTURE_HEIGHT, FRAMERATE, DISPLAY_WIDTH, DISPLAY_HEIGHT),
                                cv::CAP_GSTREAMER);
        } else if (DEVICE::WEBCAM_USB == m_activeDevId) {
            m_videoCapture.open(m_devPath.toStdString());
        } else {
            std::cerr << "unsuported device" << std::endl;
            return;
        }

        if(!m_videoCapture.isOpened()) {
            std::cout<<"Failed to open camera."<<std::endl;
            return;
        }
    }

    emit camEnabledChanged(m_camEnabled = true);
    emit averageFpsChanged(m_averageFps = m_videoCapture.get(cv::CAP_PROP_FPS));
    m_refreshTime.start(REFRESH_MULTIPLIER / m_averageFps);
}

void
VideoStreamer::closeVideoCamera()
{
    m_videoCapture.release();
    m_refreshTime.stop();
    emit camEnabledChanged(m_camEnabled = false);
}

void VideoStreamer::handleMotion()
{
    m_recognized = checkFrame(m_currentFrame, m_prevFrame, THRESHOLD_DIFF);
    emit recognizedChanged(m_recognized);

    if (m_recognized) {
        takeScreenshot();
    }

    if (m_frameCounter >= THRESHOLD_REFRESH_FRAME_COUNTER) {
        m_videoCapture >> m_prevFrame;
        m_frameCounter = 0;
        std::cout << "reset framecounter: new reference picture was created";
    } else {
        ++m_frameCounter;
    }
}

} // end namespace cam
} // end namespace cat

