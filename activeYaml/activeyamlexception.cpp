#include "activeyamlexception.h"

using namespace ActiveYaml;

ActiveYamlException::ActiveYamlException(const QString& message) :
    std::exception(),
    m_message(message)
{

}

const QString& ActiveYamlException::message() const
{
    return m_message;
}

ActiveYamlTypeException::ActiveYamlTypeException(const QString &message)
    : ActiveYamlException(message)
{

}


ActiveYamlEmitterException::ActiveYamlEmitterException(const QString &message)
    : ActiveYamlException(message)
{

}


