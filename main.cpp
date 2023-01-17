#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <opencv4/opencv2/opencv.hpp>
#include "opencvimageprovider.h"
#include "videostreamer.h"
#include <QQmlContext>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    VideoStreamer videoStreamer;

    OpencvImageProvider *liveImageProvider(new OpencvImageProvider);

    engine.rootContext()->setContextProperty("VideoStreamer",&videoStreamer);
    engine.rootContext()->setContextProperty("liveImageProvider",liveImageProvider);

    engine.addImageProvider("live",liveImageProvider);

    const QUrl url(QStringLiteral("qrc:/tabs/main_ui.qml"));

    engine.load(url);

    QObject::connect(&videoStreamer,&VideoStreamer::newImage,liveImageProvider,&OpencvImageProvider::updateImage);

    return app.exec();
}
