#include <QtGui>
#include <QtQml>
#include <opencv4/opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    engine.load(QStringLiteral("qrc:/tabs/main_ui.qml"));

//    std::string image_path = samples::findFile("starry_night.jpg");
//    Mat img = imread(image_path, IMREAD_COLOR);
//    if(img.empty())
//    {
//        std::cout << "Could not read the image: " << image_path << std::endl;
//        return 1;
//    }
//    imshow("Display window", img);
//    int k = waitKey(0); // Wait for a keystroke in the window
//    if(k == 's')
//    {
//        imwrite("starry_night.png", img);
//    }

    Mat image;

    namedWindow("Display window");

    VideoCapture cap(2);

    if (!cap.isOpened()) {

    cout << "cannot open camera";

    }

    while (true) {

    cap >> image;

    imshow("Display window", image);

    waitKey(25);

    }

    return 0;
    return 0;
}
