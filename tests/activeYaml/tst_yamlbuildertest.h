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
    void testBuildBoolean();
    void testBuildArray();
    void testBuildEmptyArray();
    void testBuildMixedArray();
    void testBuildObject();
    void testBuildNestedObject();
    void testBuildEmptyObject();

};

#endif // YAMLBUILDERTEST_H
