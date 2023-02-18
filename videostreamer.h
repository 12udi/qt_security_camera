#ifndef VIDEOSTREAMER_H
#define VIDEOSTREAMER_H

#include <QImage>
#include <QObject>
#include <QTimer>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

enum DEVICE {
    RPI_CAM = 0,
    WEBCAM_USB,
};

class VideoStreamer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool motionEnabled MEMBER m_motionEnabled NOTIFY motionEnabledChanged)
    Q_PROPERTY(int  activeDeviceId MEMBER m_devId NOTIFY activeDeviceIdChanged)
    Q_PROPERTY(bool camEnabled MEMBER m_camEnabled NOTIFY camEnabledChanged)
    Q_PROPERTY(bool recognized MEMBER m_recognized NOTIFY recognizedChanged)
    Q_PROPERTY(QString devPath MEMBER m_devPath NOTIFY devPathChanged)
    Q_PROPERTY(QString screenshotFolder MEMBER m_screenshotFolder NOTIFY screenshotFolderChanged)

public:
    VideoStreamer();
    ~VideoStreamer();

public:
    static constexpr int REFRESH_MULTIPLIER = 1000;
    static constexpr int THRESHOLD_DIFF = 1500;
    static constexpr int CAPTURE_WIDTH = 1280 ;
    static constexpr int CAPTURE_HEIGHT = 720 ;
    static constexpr int FRAMERATE = 30;
    static constexpr int DISPLAY_WIDTH = 960 ;
    static constexpr int DISPLAY_HEIGHT = 720 ;
    void streamVideo();

public slots:
    void toggleMotion(bool onoff);
    void toggleDevice(bool onoff);
    void toggleConnection(bool onoff);
    void takeScreenshot();
    void clearScreenshotFolder();

signals:
    void newImage(QImage&);
    void motionEnabledChanged(bool onoff);
    void activeDeviceIdChanged(int id);
    void camEnabledChanged(bool onoff);
    void recognizedChanged(bool yesno);
    void devPathChanged(QString path);
    void screenshotFolderChanged(QString folder);

private:
    cv::VideoCapture m_videoCapture;
    cv::Mat m_currentFrame;
    cv::Mat m_prevFrame;
    QTimer m_refreshTime;
    bool m_motionEnabled;
    bool m_camEnabled;
    bool m_recognized;
    int m_devId;
    QString m_devPath;
    QString m_screenshotFolder;

    void openVideoCamera();
    void closeVideoCamera();
    [[nodiscard]] std::string getTimestamp() const;
    [[nodiscard]] bool checkFrame(cv::Mat const& frame, cv::Mat const& prevFrame, int threshold) const;
    [[nodiscard]] std::string buildPipeline(int width, int height, int framerate, int displayWidth, int displayHeight) const;

};

#endif // VIDEOSTREAMER_H
