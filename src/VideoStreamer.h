#ifndef CAT_CAM_VIDEOSTREAMER_H
#define CAT_CAM_VIDEOSTREAMER_H

#include <QtGui/QImage>
#include <QTimer>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

enum DEVICE {
    RPI_CAM = 0,
    WEBCAM_USB,
};

namespace cat { namespace cam {

class VideoStreamer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double averageFps READ averageFps NOTIFY averageFpsChanged)
    Q_PROPERTY(int  activeDevId READ activeDevId NOTIFY activeDevIdChanged)
    Q_PROPERTY(bool motionEnabled READ motionEnabled NOTIFY motionEnabledChanged)
    Q_PROPERTY(bool camEnabled READ camEnabled NOTIFY camEnabledChanged)
    Q_PROPERTY(bool recognized READ recognized NOTIFY recognizedChanged)
    Q_PROPERTY(QString devPath MEMBER m_devPath NOTIFY devPathChanged)
    Q_PROPERTY(QString screenshotFolder MEMBER m_screenshotFolder NOTIFY screenshotFolderChanged)

public:
    VideoStreamer();
    ~VideoStreamer();

public:
    // opencv constants
    static constexpr int REFRESH_MULTIPLIER = 1000;
    static constexpr int THRESHOLD_DIFF = 1500;

    // pipeline constants
    static constexpr int CAPTURE_WIDTH = 1280 ;
    static constexpr int CAPTURE_HEIGHT = 720 ;
    static constexpr int DISPLAY_WIDTH = 960 ;
    static constexpr int DISPLAY_HEIGHT = 560 ;
    static constexpr int FRAMERATE = 30;

    //Its over 9000! 30 fps -> 9000 frames == 5min
    static constexpr int THRESHOLD_REFRESH_FRAME_COUNTER = 9000;
    void streamVideo();

    [[nodiscard]] bool recognized() const noexcept { return m_recognized; }
    [[nodiscard]] bool motionEnabled() const noexcept { return m_motionEnabled; }
    [[nodiscard]] int activeDevId() const noexcept { return m_activeDevId; }
    [[nodiscard]] bool camEnabled() const noexcept { return m_camEnabled; }
    [[nodiscard]] double averageFps() const noexcept { return m_averageFps; }

public slots:
    void toggleMotion(bool onoff);
    void toggleDevice(bool onoff);
    void toggleConnection(bool onoff);
    void takeScreenshot();
    void clearScreenshotFolder();

signals:
    void newImage(QImage&);
    void motionEnabledChanged(bool onoff);
    void activeDevIdChanged(int id);
    void camEnabledChanged(bool onoff);
    void recognizedChanged(bool yesno);
    void devPathChanged(QString path);
    void screenshotFolderChanged(QString folder);
    void averageFpsChanged(int fps);

private:
    cv::VideoCapture m_videoCapture;
    cv::Mat m_currentFrame;
    cv::Mat m_prevFrame;
    QTimer m_refreshTime;
    bool m_motionEnabled;
    bool m_camEnabled;
    bool m_recognized;
    int m_activeDevId;
    int m_frameCounter;
    double m_averageFps;
    QString m_devPath;
    QString m_screenshotFolder;

    void openVideoCamera();
    void closeVideoCamera();
    void handleMotion();
    [[nodiscard]] std::string getTimestamp() const;
    [[nodiscard]] bool checkFrame(cv::Mat const& frame, cv::Mat const& prevFrame, int threshold) const;
    [[nodiscard]] std::string buildPipeline(int width, int height, int framerate, int displayWidth, int displayHeight) const;
};

} // end namespace cam
} // end namespace cat

#endif // CAT_CAM_VIDEOSTREAMER_H
