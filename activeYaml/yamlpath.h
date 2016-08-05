#ifndef YAMLPATH_H
#define YAMLPATH_H

#include <QString>

namespace ActiveYaml
{

class YamlPathElement
{
public:
    enum class Type{
        ArrayIndex,
        ObjectProperty,
        ArrayOrObject,
        Reverse,
        Pattern,
        All,
    };
};

class YamlPath
{
public:
    YamlPath();

    static YamlPath parse(const QString& path);
};
}

#endif // YAMLPATH_H
