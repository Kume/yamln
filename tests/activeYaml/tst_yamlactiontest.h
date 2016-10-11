#ifndef YAMLACTIONTEST_H
#define YAMLACTIONTEST_H

#include <QObject>
#include <QString>
#include <QtTest>

#include "../activeYaml/activeyaml.h"

class YamlActionTest : public QObject
{
    Q_OBJECT

public:
    YamlActionTest() {}


private Q_SLOTS:
    void testModifyInteger();
};

#endif // YAMLACTIONTEST_H
