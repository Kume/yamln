#ifndef YAMLOBJECTEXCEPTION_H
#define YAMLOBJECTEXCEPTION_H

#include "yamlnexception.h"
#include "yamlobject.h"

namespace ActiveYaml {

class YamlObjectException : public YamlnException
{
public:
    YamlObjectException(const QString& message, YamlObjectPtr context);

    YamlObject& context() const;

private:
    YamlObjectPtr m_context;
};

}

#endif // YAMLOBJECTEXCEPTION_H
