#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "OpencvImageProvider.h"
#include "VideoStreamer.h"
#include <QQmlContext>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int
main(int argc, char* argv[])
{
  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;

  cat::cam::VideoStreamer videoStreamer;
  cat::cam::OpencvImageProvider* liveImageProvider(new cat::cam::OpencvImageProvider);

  engine.rootContext()->setContextProperty("videoStreamer", &videoStreamer);
  engine.rootContext()->setContextProperty("liveImageProvider", liveImageProvider);
  engine.addImageProvider("live", liveImageProvider);
  const QUrl url(QStringLiteral("qrc:/MainUI.qml"));
  engine.load(url);

  QObject::connect(
    &videoStreamer, &cat::cam::VideoStreamer::newImage, liveImageProvider, &cat::cam::OpencvImageProvider::updateImage);

  return app.exec();
}
