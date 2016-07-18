#include "yamlobjectexception.h"

using namespace ActiveYaml;

YamlObjectException::YamlObjectException(const QString& message, YamlObjectPtr context) :
    YamlnException(message)
{
    m_context = context;
}

YamlObject& YamlObjectException::context() const
{
    return *m_context;
}
