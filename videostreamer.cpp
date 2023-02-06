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

  //  cv::imshow("frame", frame);
  //  cv::imshow("prevframe", prevFrame);

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

void
VideoStreamer::openVideoCamera(QString devicePath)
{
  if (devicePath.length() == 1) {
    m_VideoCapture.open(devicePath.toInt());
  } else {
    m_VideoCapture.open(devicePath.toStdString());
  }

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
