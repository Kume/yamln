#ifndef YAMLNEXCEPTION_H
#define YAMLNEXCEPTION_H

#include <exception>
#include <QString>

class YamlnException : std::exception
{
public:
    YamlnException(const QString& message);

    const QString& message() const;
private:
    QString m_message;
};

#endif // YAMLNEXCEPTION_H
