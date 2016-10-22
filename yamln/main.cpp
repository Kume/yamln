#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "activeyaml.h"
#include "yamlobjectparser.h"
#include <QList>
#include <QFile>
#include <QDir>
#include "uiviewmodel/rootuiviewmodel.h"
#include <QDebug>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "uiviewmodel/uiviewmodellist.h"
#include "uiviewmodel/formuiviewmodel.h"
#include "uiviewmodel/formelementuiviewmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<UIViewModelList>("yamln", 0, 1, "UIViewModelList");
    qmlRegisterType<UIViewModel>("yamln", 0, 1, "UIViewModel");
    qmlRegisterUncreatableType<FormUIViewModel>("yamln", 0, 1, "FormUIViewModel", "");
    qmlRegisterUncreatableType<FormElementUIViewModel>("yamln", 0, 1, "FormElementUIViewModel", "");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    YamlObjectParser::isDebugOutputEnabled = true;
    auto parsed = YamlObjectParser::fromFile(QFile(":/samples/sample1.yaml"));

    auto uiViewModel = new RootUIViewModel(0, parsed);
    engine.rootContext()->setContextProperty("test", uiViewModel);

    return app.exec();
}
