#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <../libyaml/yamlobject.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    YamlObject::fromFile(QString("C:\\Users\\makoto\\c\\qt_test\\test.yaml"));

    return app.exec();
}
