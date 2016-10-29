#include "tst_yamlbuildertest.h"

#include <QTest>
#include <yamlobject.h>
#include <yamlbuider.h>

using namespace ActiveYaml;

void YamlBuilderTest::testBuildInteger()
{
    auto b = YamlBuider();
    auto y = b(1);
    QCOMPARE(y->type(), YamlObject::TypeInteger);
    QCOMPARE(y->integerValue(), 1);
}

void YamlBuilderTest::testBuildFloat()
{
    auto b = YamlBuider();
    auto y = b(1.25);
    QCOMPARE(y->type(), YamlObject::TypeFloat);
    // QCOMPARE(y->floatValue(), 1.25);
}

void YamlBuilderTest::testBuildString()
{
    auto b = YamlBuider();
    auto y = b("hoge");
    QCOMPARE(y->type(), YamlObject::TypeString);
    QCOMPARE(y->stringValue(), QString("hoge"));
}
