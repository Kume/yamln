#include "tst_yamlactiontest.h"

#include "action/modifyyamlaction.h"
#include <yamlmanager.h>

using namespace ActiveYaml;

void YamlActionTest::testInteger()
{

}

void YamlActionTest::testModifyInteger()
{
    auto manager = new YamlMa
    auto action = new ModifyYamlAction(YamlPath::parse("test"), YamlObject::integer(2));
}
