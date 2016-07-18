#ifndef UIDEFINITIONEXCEPTION_H
#define UIDEFINITIONEXCEPTION_H

#include "yamlnexception.h"
#include "yamlobject.h"

using namespace ActiveYaml;

class UIDefinitionException : public YamlnException
{
public:
    explicit UIDefinitionException(const QString &message, const YamlObjectPtr &context);

    YamlObjectPtr context() const;

private:
    YamlObjectPtr m_context;
};

#endif // UIDEFINITIONEXCEPTION_H
