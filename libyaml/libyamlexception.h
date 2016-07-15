#ifndef LIBYAMLEXCEPTION_H
#define LIBYAMLEXCEPTION_H

#include <exception>
#include <QString>

class LibYamlException : std::exception
{
public:
    LibYamlException(const QString& message);

    const QString& message() const;
private:
    QString m_message;
};

class LibYamlTypeException : LibYamlException
{
public:
    LibYamlTypeException(const QString &message);
};

class LibYamlEmitterException : LibYamlException
{
public:
    LibYamlEmitterException(const QString &message);
};

#endif // LIBYAMLEXCEPTION_H
