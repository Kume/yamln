#include "tst_yamlbuildertest.h"

#include <QTest>
#include <yamlobject.h>
#include <yamlbuilder.h>

using namespace ActiveYaml;

void YamlBuilderTest::testBuildInteger()
{
    auto b = YamlBuilder();
    auto y = b(1);
    QCOMPARE(y->type(), YamlObject::TypeInteger);
    QCOMPARE(y->integerValue(), 1);
}

void YamlBuilderTest::testBuildFloat()
{
    auto b = YamlBuilder();
    auto y = b(1.25);
    QCOMPARE(y->type(), YamlObject::TypeFloat);
    // QCOMPARE(y->floatValue(), 1.25);
}

void YamlBuilderTest::testBuildString()
{
    auto y = YamlBuilder()("hoge");
    QCOMPARE(y->type(), YamlObject::TypeString);
    QCOMPARE(y->stringValue(), QString("hoge"));
}

void YamlBuilderTest::testBuildBoolean()
{
    auto y = YamlBuilder()(true);
    QCOMPARE(y->type(), YamlObject::TypeBoolean);
    // QCOMPARE(y->boolValue(), true);
}

void YamlBuilderTest::testBuildArray()
{
    auto y = YamlBuilder().array(1);
    QCOMPARE(y->type(), YamlObject::TypeArray);

    // TODO 配列のサイズの確認
    // TODO 配列の中身の確認
}

void YamlBuilderTest::testBuildEmptyArray()
{
    auto y = YamlBuilder().array();
//    QCOMPARE(y->type(), YamlObject::TypeArray);
    // TODO 配列のサイズの確認
}

void YamlBuilderTest::testBuildMixedArray()
{
    auto b = YamlBuilder();
    auto y = b.array(1, "test", b(2));
//    QCOMPARE(y->type(), YamlObject::TypeArray);
    // TODO 配列のサイズの確認
    // TODO 配列の中身の確認
}

void YamlBuilderTest::testBuildObject()
{
    auto y = YamlBuilder().object({
        {1, 2},
        {"hoge", "fuga"}
    });

    QCOMPARE(y->type(), YamlObject::TypeObject);
    // TODO 値の一致判定
}

void YamlBuilderTest::testBuildNestedObject()
{
    auto b = YamlBuilder();
    auto y = b.object({
        {"hoge", "test"},
        {"fuga", {
            {"foo", 1},
            {"bar", 4}
        }},
    });
    QCOMPARE(y->type(), YamlObject::TypeObject);
}

void YamlBuilderTest::testBuildEmptyObject()
{
    auto y = YamlBuilder().object({});
    QCOMPARE(y->type(), YamlObject::TypeObject);
    // TODO サイズ判定
}
