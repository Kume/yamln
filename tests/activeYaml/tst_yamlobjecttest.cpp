#include "tst_yamlobjecttest.h"

#include "yamlbuilder.h"

using namespace ActiveYaml;

// TODO 共有の場所に移動
void compareYamlObject(YamlObjectPtr actual, int expected)
{
    QCOMPARE(actual->type(), YamlObject::TypeInteger);
    QCOMPARE(actual->integerValue(), expected);
}

void compareYamlObject(YamlObjectPtr actual, const char* expected)
{
    QCOMPARE(actual->type(), YamlObject::TypeString);
    QCOMPARE(actual->stringValue(), QString(expected));
}


YamlObjectTest::YamlObjectTest()
{
}

void YamlObjectTest::testInteger()
{
    YamlObjectPtr integerYaml = YamlObject::integer(3);
    QVERIFY2(integerYaml->type() == YamlObject::TypeInteger, "Wrong Type.");
    QVERIFY2(integerYaml->integerValue() == 3, "Wrong Value.");
}


void YamlObjectTest::testString()
{
    YamlObjectPtr stringYaml = YamlObject::string("test");
    QCOMPARE(stringYaml->type(), YamlObject::TypeString);
    QCOMPARE(stringYaml->stringValue(), QString("test"));
}

void YamlObjectTest::testIteratorForArray()
{
    YamlBuilder b;
    auto a = b.array(3, "test");
    auto i = a->begin();
    compareYamlObject(*i++, 3);
    compareYamlObject(*i++, "test");
    QCOMPARE(i, a->end());
}
