#include "tst_yamlpathtest.h"

using namespace ActiveYaml;


void compareElement(YamlPathElement element, YamlPathType type, QString name)
{
    QCOMPARE(element.type(), type);
    QCOMPARE(element.property(), name);
}

void compareElement(YamlPathElement element, YamlPathType type, int index)
{
    QCOMPARE(element.type(), type);
    QCOMPARE(element.index(), index);
}

YamlPathTest::YamlPathTest()
{

}

void YamlPathTest::testParseEmpty()
{
    YamlPath path = YamlPath::parse("");
    QVERIFY2(path.isEmpty(), "Is not empty.");
}

void YamlPathTest::testParseSingleProperty()
{
    YamlPath path = YamlPath::parse("hoge");
    QCOMPARE(path.size(), 1);
    compareElement(path.first(), YamlPathType::PropertyOrIndex, "hoge");
}

void YamlPathTest::testParseRoot()
{
    YamlPath path = YamlPath::parse("/");
    QCOMPARE(path.size(), 1);
    QCOMPARE(path.first().type(), YamlPathType::Root);
}

void YamlPathTest::testParseAll()
{
    YamlPath path = YamlPath::parse("*");
    QCOMPARE(path.size(), 1);
    QCOMPARE(path.first().type(), YamlPathType::All);
}
