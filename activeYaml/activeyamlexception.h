#ifndef ACTIVEYAMLEXCEPTION_H
#define ACTIVEYAMLEXCEPTION_H

#include <exception>
#include <QString>

namespace ActiveYaml {

class ActiveYamlException : std::exception
{
public:
    ActiveYamlException(const QString& message);

    const QString& message() const;
private:
    QString m_message;
};

class ActiveYamlTypeException : ActiveYamlException
{
public:
    ActiveYamlTypeException(const QString &message);
};

class ActiveYamlEmitterException : ActiveYamlException
{
public:
    ActiveYamlEmitterException(const QString &message);
};

}

#endif // ACTIVEYAMLEXCEPTION_H
