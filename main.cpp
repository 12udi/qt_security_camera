#include <QtGui>
#include <QtQml>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QStringLiteral("qrc:/tabs/main_ui.qml"));

    return app.exec();
}
