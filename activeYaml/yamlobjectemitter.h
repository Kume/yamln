#ifndef YAMLOBJECTEMITTER_H
#define YAMLOBJECTEMITTER_H

#include <QString>
#include <QVariant>
#include "yamlobject.h"

namespace ActiveYaml
{
class YamlObjectEmitter
{
    YamlObjectEmitter();

public:
    static QString dump(const YamlObjectPtr &yamlObject);
    static QVariant toQVariant(const YamlObjectPtr &yamlObject);

private:
    static void emitYaml(const YamlObjectPtr &yamlObject, void* emitter);

};
}

#endif // YAMLOBJECTEMITTER_H
