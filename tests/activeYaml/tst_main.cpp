#include "tst_yamlobjecttest.h"
#include "tst_yamlactiontest.h"
#include "tst_yamlpathtest.h"
#include "tst_yamlmanagertest.h"

#include <QtTest>

int main(int argc, char *argv[])
{
    {
        YamlObjectTest test;
        QTest::qExec(&test, argc, argv);
    }

    {
        YamlActionTest test;
        QTest::qExec(&test, argc, argv);
    }

    {
        YamlPathTest test;
        QTest::qExec(&test, argc, argv);
    }

    {
        YamlManagerTest test;
        QTest::qExec(&test, argc, argv);
    }

    return 0;
}

// QTEST_APPLESS_MAIN(YamlObjectTest)
