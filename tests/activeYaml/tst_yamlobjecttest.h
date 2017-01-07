#ifndef YAMLOBJECTTEST_H
#define YAMLOBJECTTEST_H

#include <QObject>
#include <QString>
#include <QtTest>

#include "../activeYaml/activeyaml.h"

class YamlObjectTest : public QObject
{
    Q_OBJECT

public:
    YamlObjectTest();

private Q_SLOTS:
    void testInteger();
    void testString();

    void testIteratorForArray();
};

#endif // YAMLOBJECTTEST_H
