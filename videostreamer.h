#ifndef VIDEOSTREAMER_H
#define VIDEOSTREAMER_H

#include <QImage>
#include <QObject>
#include <QTimer>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class VideoStreamer : public QObject
{
  Q_OBJECT
  Q_PROPERTY(bool recognizedMotion MEMBER m_RecognizedMotion NOTIFY recognizedChanged)

public:
  VideoStreamer();
  ~VideoStreamer();

public:
  void streamVideo();

public slots:
  void openVideoCamera(QString devicePath);
  void closeVideoCamera();
  void takeScreenshot(QString screenshotPath);
  void clearScreenshotFolder();
  std::string gstreamer_pipeline(int device, int capture_width, int capture_height, int framerate, int display_width, int display_height);


private:
  static constexpr int REFRESH_MULTIPLIER = 1000;

  cv::Mat m_CurrentFrame;
  cv::Mat m_PrevFrame;
  cv::VideoCapture m_VideoCapture;
  QTimer m_RefreshTime;
  bool m_CameraIsOpen;
  bool m_FolderExists;
  bool m_MotionDetectionActive;
  bool m_RecognizedMotion;
  QString m_DevicePath;
  QString m_ScreenshotPath;
  std::string getTimestamp();
  bool checkFrame(cv::Mat const& frame, cv::Mat const& prevFrame, int threshold);

signals:
  void newImage(QImage&);
  void recognizedChanged(bool recognized);
};

#endif // VIDEOSTREAMER_H
