#include "libyamlexception.h"

LibYamlException::LibYamlException(const QString& message) :
    std::exception(),
    m_message(message)
{

}

const QString& LibYamlException::message() const
{
    return m_message;
}

LibYamlTypeException::LibYamlTypeException(const QString &message)
    : LibYamlException(message)
{

}


LibYamlEmitterException::LibYamlEmitterException(const QString &message)
    : LibYamlException(message)
{

}


