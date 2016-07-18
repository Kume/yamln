#include "tst_yamlobjecttest.h"

using namespace ActiveYaml;

YamlObjectTest::YamlObjectTest()
{
}

void YamlObjectTest::testInteger()
{
    YamlObjectPtr integerYaml = YamlObjectPtr(YamlObject::integer(3));
    QVERIFY2(integerYaml->type() == YamlObject::TypeInteger, "Wrong Type.");
    QVERIFY2(integerYaml->integerValue() == 3, "Wrong Value.");
}


void YamlObjectTest::testString()
{
    YamlObjectPtr stringYaml = YamlObjectPtr(YamlObject::string("test"));
    QCOMPARE(stringYaml->type(), YamlObject::TypeString);
    QCOMPARE(stringYaml->stringValue(), QString("test"));
}
