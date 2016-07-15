#include "yamlnexception.h"


YamlnException::YamlnException(const QString& message) :
    std::exception(),
    m_message(message)
{

}

const QString& YamlnException::message() const
{
    return m_message;
}
