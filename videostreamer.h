#ifndef VIDEOSTREAMER_H
#define VIDEOSTREAMER_H

#include <QObject>
#include <QTimer>
#include <opencv2/highgui.hpp>
#include <QImage>
#include <iostream>

class VideoStreamer: public QObject
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
    void takeScreenshot();

private:
    cv::Mat m_CurrentFrame;
    cv::VideoCapture m_VideoCapture;
    QTimer m_RefreshTime;
    bool m_CameraIsOpen;
    QString m_DevicePath;

signals:
    void newImage(QImage &);
};

#endif // VIDEOSTREAMER_H
