#ifndef YAMLOBJECTPARSER_H
#define YAMLOBJECTPARSER_H

#include "yamlobject.h"

namespace ActiveYaml
{

class YamlObjectParser
{
public:
    YamlObjectParser();

    static bool isDebugOutputEnabled;

    static YamlObjectPtr fromFile(const QString &fileName);
    static YamlObjectPtr fromFile(QFile &file);

private:
    static YamlObjectPtr parse(void* parser);
};

}

#endif // YAMLOBJECTPARSER_H
