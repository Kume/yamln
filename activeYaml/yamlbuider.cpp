#include "yamlbuider.h"

using namespace ActiveYaml;

YamlBuider::YamlBuider()
{

}

ActiveYaml::YamlObjectPtr YamlBuider::operator()(const QString &value)
{
    return YamlObject::string(value);
}

ActiveYaml::YamlObjectPtr YamlBuider::operator()(int value)
{
    return YamlObject::integer(value);
}

ActiveYaml::YamlObjectPtr YamlBuider::operator ()(double value)
{
    return YamlObject::float_(value);
}
