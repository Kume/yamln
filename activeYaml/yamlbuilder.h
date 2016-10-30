#ifndef YAMLBUILDER_H
#define YAMLBUILDER_H

#include <QString>
#include <initializer_list>
#include "yamlobject.h"

namespace ActiveYaml
{
class YamlObjectKeyPair
{
public:
    template<typename KeyType, typename ValueType>
    YamlObjectKeyPair(KeyType key, ValueType value) :
        m_key(YamlBuilder()(key)),
        m_value(YamlBuilder()(value))
    {

    }

    template<typename KeyType>
    YamlObjectKeyPair(KeyType key, const std::vector<YamlObjectKeyPair>& values) :
        m_key(YamlBuilder()(key)),
        m_value(YamlBuilder().object(values))
    {

    }

    YamlObjectPtr key() const { return m_key; }
    YamlObjectPtr value() const { return m_value; }

private:
    YamlObjectPtr m_key;
    YamlObjectPtr m_value;
};

class YamlBuilder
{
public:
    YamlBuilder();

    YamlObjectPtr operator ()(int value) const;
    YamlObjectPtr operator ()(double value) const;
    YamlObjectPtr operator ()(bool value) const;
    YamlObjectPtr operator ()(const YamlObjectPtr& value) const;
    YamlObjectPtr operator ()(const QString& value) const;
    YamlObjectPtr operator ()(const char* value) const;

    YamlObjectPtr object(const std::vector<YamlObjectKeyPair>& args) const;

    template<typename First, typename... Rest>
    YamlObjectPtr array(First first, Rest... rest)
    {
        YamlObjectPtr y = this->array(rest...);
        y->insert(0, (*this)(first));
        return y;
    }

    YamlObjectPtr array()
    {
        return YamlObject::array();
    }
};
}

#endif // YAMLBUILDER_H
