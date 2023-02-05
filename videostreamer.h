#ifndef VIDEOSTREAMER_H
#define VIDEOSTREAMER_H

#include <QImage>
#include <QObject>
#include <QTimer>
#include <iostream>
#include <opencv2/highgui.hpp>

class VideoStreamer : public QObject
{
  Q_OBJECT
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

private:
  cv::Mat m_CurrentFrame;
  cv::VideoCapture m_VideoCapture;
  QTimer m_RefreshTime;
  bool m_CameraIsOpen;
  bool m_FolderExists;
  QString m_DevicePath;
  QString m_ScreenshotPath;
  std::string getTimestamp();

signals:
  void newImage(QImage&);
};

#endif // VIDEOSTREAMER_H
