#include "modifyyamlaction.h"

using namespace ActiveYaml;

ModifyYamlAction::ModifyYamlAction(const YamlPath &path, const YamlObjectPtr &value)
{

}

YamlActionPtr ActiveYaml::ModifyYamlAction::apply(YamlObjectPtr target)
{
    return YamlActionPtr(0);
}
