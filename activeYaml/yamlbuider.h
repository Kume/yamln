#ifndef YAMLBUIDER_H
#define YAMLBUIDER_H

#include <QString>
#include "yamlobject.h"

namespace ActiveYaml {
class YamlBuider
{
public:
    YamlBuider();

    YamlObjectPtr operator()(const QString& value);
    YamlObjectPtr operator()(int value);
    YamlObjectPtr operator ()(double value);
};
}

#endif // YAMLBUIDER_H
