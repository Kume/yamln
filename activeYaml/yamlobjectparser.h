#ifndef YAMLOBJECTPARSER_H
#define YAMLOBJECTPARSER_H

#include "yamlobject.h"

namespace ActiveYaml
{

class YamlObjectParser
{
public:
    YamlObjectParser();

    static YamlObjectPtr fromFile(const QString &fileName);
    static YamlObjectPtr fromFile(QFile &file);
};

}

#endif // YAMLOBJECTPARSER_H
