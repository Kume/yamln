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
    QCOMPARE(path.isAbsolute(), false);
    QCOMPARE(path.size(), 1);
    compareElement(path.first(), YamlPathType::PropertyOrIndex, "hoge");
}

void YamlPathTest::testParseMultiProperty()
{
    YamlPath path = YamlPath::parse("hoge.huga");
    QCOMPARE(path.size(), 2);
    compareElement(path.elementAt(0), YamlPathType::PropertyOrIndex, "hoge");
    compareElement(path.elementAt(1), YamlPathType::PropertyOrIndex, "huga");
}

void YamlPathTest::testParseRoot()
{
    YamlPath path = YamlPath::parse("/");
    QCOMPARE(path.size(), 0);
}

void YamlPathTest::testAbsoluteSinglePath()
{
    YamlPath path = YamlPath::parse("/hoge");
    QCOMPARE(path.isAbsolute(), true);
    QCOMPARE(path.size(), 1);
    compareElement(path.elementAt(0), YamlPathType::PropertyOrIndex, "hoge");
}

void YamlPathTest::testAbsoluteMultiPath()
{
    YamlPath path = YamlPath::parse("/hoge.huga");
    QCOMPARE(path.isAbsolute(), true);
    QCOMPARE(path.size(), 2);
    compareElement(path.elementAt(0), YamlPathType::PropertyOrIndex, "hoge");
    compareElement(path.elementAt(1), YamlPathType::PropertyOrIndex, "huga");
}

void YamlPathTest::testParseAll()
{
    YamlPath path = YamlPath::parse("*");
    QCOMPARE(path.size(), 1);
    QCOMPARE(path.first().type(), YamlPathType::All);
}
