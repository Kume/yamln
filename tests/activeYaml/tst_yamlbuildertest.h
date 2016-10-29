#ifndef YAMLBUILDERTEST_H
#define YAMLBUILDERTEST_H

#include <QObject>

class YamlBuilderTest : public QObject
{
    Q_OBJECT

public:
    YamlBuilderTest() {}

private Q_SLOTS:
    void testBuildInteger();
    void testBuildFloat();
    void testBuildString();
};

#endif // YAMLBUILDERTEST_H
