#include "videostreamer.h"
#include <QDateTime>
#include <filesystem>

VideoStreamer::VideoStreamer()
  : m_CurrentFrame()
  , m_PrevFrame()
  , m_VideoCapture()
  , m_RefreshTime()
  , m_CameraIsOpen(false)
  , m_FolderExists(false)
  , m_MotionDetectionActive(true)
  , m_RecognizedMotion(false)
  , m_DevicePath("0")
  , m_ScreenshotPath("~/screenshots")
{
  connect(&m_RefreshTime, &QTimer::timeout, this, &VideoStreamer::streamVideo);
}

VideoStreamer::~VideoStreamer()
{
  closeVideoCamera();
}

void
VideoStreamer::streamVideo()
{
  static constexpr int THRESHOLD_DIFF = 1500;

  m_VideoCapture >> m_CurrentFrame;

  QImage img =
    QImage(m_CurrentFrame.data, m_CurrentFrame.cols, m_CurrentFrame.rows, QImage::Format_RGB888)
      .rgbSwapped();
  emit newImage(img);

  // handle first frame
  if (m_PrevFrame.empty()) {
    m_VideoCapture >> m_PrevFrame;
    std::cout << "m_MotionDetectionActive: " << m_MotionDetectionActive << std::endl;
    return;
  }

  if (m_MotionDetectionActive) {
    m_RecognizedMotion = checkFrame(m_CurrentFrame, m_PrevFrame, THRESHOLD_DIFF);
    emit recognizedChanged(m_RecognizedMotion);
  }
}

bool
VideoStreamer::checkFrame(const cv::Mat& frame, const cv::Mat& prevFrame, int threshold)
{
  cv::Mat grayFrame;
  cv::Mat grayPrevFrame;
  cv::Mat diffFrame;
  cv::Mat thresholdFrame;
  bool result = false;

  cv::imshow("test", frame);

  cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
  cv::cvtColor(prevFrame, grayPrevFrame, cv::COLOR_BGR2GRAY);
  cv::absdiff(grayFrame, grayPrevFrame, diffFrame);
  cv::threshold(diffFrame, thresholdFrame, 127, 1, cv::THRESH_BINARY);

  if (cv::countNonZero(thresholdFrame) >= threshold) {
    result = true;
  }

  return result;
}

void
VideoStreamer::takeScreenshot(QString screenshotPath)
{
  if (!m_CameraIsOpen) {
    std::cerr << "open stream first before taking screenshot" << std::endl;
    return;
  }

  if (!m_FolderExists) {
    m_FolderExists = std::filesystem::create_directories(screenshotPath.toStdString());
    m_ScreenshotPath = screenshotPath;
  }

  if (m_CurrentFrame.empty()) {
    std::cerr << "Something is wrong with the webcam, could not get frame." << std::endl;
  } else {
    std::string fileName = screenshotPath.toStdString() + "/" + getTimestamp() + ".jpg";
    cv::imwrite(fileName, m_CurrentFrame);
  }
}

void
VideoStreamer::clearScreenshotFolder()
{
  uint32_t error = std::filesystem::remove_all(m_ScreenshotPath.toStdString());

  if (error == 2 || error == 0) {
    m_FolderExists = false;
  } else {
    std::cout << "Error: " << strerror(error) << std::endl;
  }
}

std::string
VideoStreamer::getTimestamp()
{
  QDateTime now = QDateTime::currentDateTime();
  QString timestamp = now.toString(QLatin1String("ddMMyyyy-hhmmss"));
  return QString::fromLatin1("pic%1").arg(timestamp).toStdString();
}

std::string VideoStreamer::gstreamer_pipeline(int device, int capture_width, int capture_height, int framerate, int display_width, int display_height) {
    return
            " libcamerasrc !"
            " video/x-raw,"
            " width=(int)" + std::to_string(capture_width) + ","
            " height=(int)" + std::to_string(capture_height) + ","
            " framerate=(fraction)" + std::to_string(framerate) +"/1 !"
            " videoconvert ! videoscale !"
            " video/x-raw,"
            " width=(int)" + std::to_string(display_width) + ","
            " height=(int)" + std::to_string(display_height) + " ! appsink";
}

void
VideoStreamer::openVideoCamera(QString /*devicePath*/)
{
    int device = 0;                 //0=raspicam 1=usb webcam (when both are connected)
    int capture_width = 1280 ;
    int capture_height = 720 ;
    int framerate = 30 ;
    int display_width = 1280 ;
    int display_height = 720 ;

    std::string pipeline = gstreamer_pipeline(device,
                                              capture_width, capture_height, framerate,
                                              display_width, display_height);
    std::cout << "Using pipeline: \n\t" << pipeline << "\n\n\n";

    cv::VideoCapture cap(pipeline, cv::CAP_GSTREAMER);
    if(!cap.isOpened()) {
        std::cout<<"Failed to open camera."<<std::endl;
        return;
    }
    m_VideoCapture = cap;

    double fps = m_VideoCapture.get(cv::CAP_PROP_FPS);
    m_RefreshTime.start(REFRESH_MULTIPLIER / fps);
    m_CameraIsOpen = true;
}

void
VideoStreamer::closeVideoCamera()
{
  m_VideoCapture.release();
  m_RefreshTime.stop();
  m_CameraIsOpen = false;
}
