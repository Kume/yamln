#include "tst_yamlobjecttest.h"
#include "tst_yamlactiontest.h"
#include "tst_yamlpathtest.h"
#include "tst_yamlmanagertest.h"
#include "tst_yamlbuildertest.h"

#include <QtTest>

template<typename TestType>
void execTest(int argc, char *argv[])
{
    TestType test;
    QTest::qExec(&test, argc, argv);
}

int main(int argc, char *argv[])
{
    execTest<YamlObjectTest>(argc, argv);
    execTest<YamlActionTest>(argc, argv);
    execTest<YamlPathTest>(argc, argv);
    execTest<YamlManagerTest>(argc, argv);
    execTest<YamlBuilderTest>(argc, argv);

    return 0;
}

// QTEST_APPLESS_MAIN(YamlObjectTest)
