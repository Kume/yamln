#include "activeyamlutil.h"

#include <QRegExp>

using namespace ActiveYaml;

bool ActiveYamlUtil::isIntegerString(const QString &string)
{
    static QRegExp isInteger("^\\d+$");
    return isInteger.exactMatch(string);
}

bool ActiveYamlUtil::isFloatString(const QString &string)
{
    static QRegExp isFloat("^\\d+\\.\\d+");
    return isFloat.exactMatch(string);
}
