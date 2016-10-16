#ifndef UTIL_H
#define UTIL_H

#include <QString>

namespace ActiveYaml
{
class ActiveYamlUtil
{
private:
    ActiveYamlUtil() {}

public:

    static bool isIntegerString(const QString &string);
    static bool isFloatString(const QString &string);
};
}

#endif // UTIL_H
