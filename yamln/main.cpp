#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <../libyaml/yamlobject.h>
#include <QList>
#include <QFile>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    YamlObject::fromFile(QString("C:\\Users\\makoto\\c\\qt_test\\test.yaml"));

    QList<int> l;
    l.at(19);
    l[10] = 10;
    QFile f("");
    f.read(0, 100);

    return app.exec();
}
