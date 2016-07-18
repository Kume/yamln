#ifndef YAMLACTION_H
#define YAMLACTION_H

#include <QSharedPointer>

#include "yamlobject.h"
#include "yamlpath.h"

namespace ActiveYaml
{
class YamlAction;

typedef QSharedPointer<YamlAction> YamlActionPtr;

class YamlAction
{
public:
    YamlAction();
    virtual ~YamlAction();

    virtual YamlActionPtr apply(YamlObjectPtr target) = 0;
};
}

#endif // YAMLACTION_H
