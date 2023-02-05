#include "videostreamer.h"

VideoStreamer::VideoStreamer()
    : m_CurrentFrame()
    , m_VideoCapture()
    , m_RefreshTime()
    , m_CameraIsOpen(false)
    , m_DevicePath("/dev/video0")
{
    connect(&m_RefreshTime,&QTimer::timeout,this,&VideoStreamer::streamVideo);
}

VideoStreamer::~VideoStreamer()
{
    closeVideoCamera();
}

void VideoStreamer::streamVideo()
{
    m_VideoCapture >> m_CurrentFrame;

    QImage img = QImage(m_CurrentFrame.data,m_CurrentFrame.cols,m_CurrentFrame.rows,QImage::Format_RGB888).rgbSwapped();
    emit newImage(img);
}

void VideoStreamer::takeScreenshot()
{
    if(!m_CameraIsOpen) {
        std::cerr << "open stream first before taking screenshot" << std::endl;
        return;
    }

    cv::Mat save_img;
    m_VideoCapture >> save_img;

    if(save_img.empty()) {
      std::cerr << "Something is wrong with the webcam, could not get frame." << std::endl;
    }

    // Save the frame into a file
    cv::imwrite("test.jpg", save_img);
}

void VideoStreamer::openVideoCamera(QString devicePath)
{
    if(devicePath.length() == 1) {
        m_VideoCapture.open(devicePath.toInt());
    }
    else {
        m_VideoCapture.open(devicePath.toStdString());
    }

    double fps = m_VideoCapture.get(cv::CAP_PROP_FPS);
    m_RefreshTime.start(1000/fps);
    m_CameraIsOpen = true;

}

void VideoStreamer::closeVideoCamera()
{
    m_VideoCapture.release();
    m_RefreshTime.stop();
    m_CameraIsOpen = false;
}
