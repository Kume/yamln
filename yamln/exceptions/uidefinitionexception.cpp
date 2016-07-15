#include "uidefinitionexception.h"

UIDefinitionException::UIDefinitionException(const QString &message, const YamlObjectPtr &context) :
    YamlnException(message),
    m_context(context)
{

}

YamlObjectPtr UIDefinitionException::context() const
{
    return m_context;
}
