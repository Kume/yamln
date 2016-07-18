#ifndef MODIFYYAMLACTION_H
#define MODIFYYAMLACTION_H

#include "yamlaction.h"

namespace ActiveYaml
{

class ModifyYamlAction : public YamlAction
{
public:
    ModifyYamlAction(const YamlPath &path, const YamlObjectPtr &value);


private:
    YamlPath m_path;
    YamlObjectPtr m_newValue;
    YamlObjectPtr m_oldValue;

    // YamlAction interface
public:
    virtual YamlActionPtr apply(YamlObjectPtr target) override;
};
}

#endif // MODIFYYAMLACTION_H
