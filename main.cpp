#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "opencvimageprovider.h"
#include "videostreamer.h"
#include <QQmlContext>
#include <iostream>

#include "opencv4/opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/tracking.hpp"

using namespace cv;
using namespace std;

bool check_frame(Mat frame, Mat prev_frame, int t){
    Mat eval1, eval2, diff, thresh;
    cvtColor(frame, eval1, COLOR_BGR2GRAY);
    cvtColor(prev_frame, eval2, COLOR_BGR2GRAY);
    absdiff(eval1, eval2, diff);
    threshold(diff, thresh, 127, 1, THRESH_BINARY);
    int n_values = countNonZero(thresh);

    if (n_values >= t){
        return true;
    }
    else{
        return false;
    }
}

int main(int argc, char *argv[])
{
    //    QGuiApplication app(argc, argv);

    //    QQmlApplicationEngine engine;

    //    VideoStreamer videoStreamer;

    //    OpencvImageProvider *liveImageProvider(new OpencvImageProvider);

    //    engine.rootContext()->setContextProperty("VideoStreamer",&videoStreamer);
    //    engine.rootContext()->setContextProperty("liveImageProvider",liveImageProvider);

    //    engine.addImageProvider("live",liveImageProvider);

    //    const QUrl url(QStringLiteral("qrc:/tabs/main_ui.qml"));

    //    engine.load(url);

    //    QObject::connect(&videoStreamer,&VideoStreamer::newImage,liveImageProvider,&OpencvImageProvider::updateImage);


    // Create video capturing object
    // 0 opens default camera, otherwise filename as argument
    cv::VideoCapture video(0);

    // Check that video is opened
    if (!video.isOpened()) return -1;

    // For saving the frame
    cv::Mat frame;

    // Get video resolution
    int frameWidth = video.get(cv::CAP_PROP_FRAME_WIDTH);
    int frameHeigth = video.get(cv::CAP_PROP_FRAME_HEIGHT);

    // Create video writer object
    cv::VideoWriter output("output.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size(frameWidth, frameHeigth));

    // Create tracker, select region-of-interest (ROI) and initialize the tracker
    cv::Ptr<cv::Tracker> tracker = cv::TrackerKCF::create();
    video.read(frame);
    cv::Rect2d trackingBox = cv::selectROI(frame, false);
    tracker->init(frame, trackingBox);

    // Loop through available frames
    while (video.read(frame)) {

        // Update the tracker and draw the rectangle around target if update was successful
        if (tracker->update(frame, trackingBox)) {
            cv::rectangle(frame, trackingBox, cv::Scalar(255, 0, 0), 2, 8);
        }

        // Display the frame
        cv::imshow("Video feed", frame);

        // Write video frame to output
        output.write(frame);

        // For breaking the loop
        if (cv::waitKey(25) >= 0) break;

    } // end while (video.read(frame))

    // Release video capture and writer
    output.release();
    video.release();

    // Destroy all windows
    cv::destroyAllWindows();

    return 0;
    //    return app.exec();
}
