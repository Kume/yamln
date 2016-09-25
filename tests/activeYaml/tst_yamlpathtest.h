#ifndef TST_YAMLPATH_H
#define TST_YAMLPATH_H

#include <QObject>
#include <QString>
#include <QtTest>

#include "../activeYaml/activeyaml.h"

class YamlPathTest : public QObject
{
    Q_OBJECT

public:
    YamlPathTest();

private Q_SLOTS:
    void testParseEmpty();
    void testParseSingleProperty();
    void testParseRoot();
    void testParseAll();
};

#endif // TST_YAMLPATH_H
