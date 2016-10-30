#include "yamlbuilder.h"

using namespace ActiveYaml;

YamlBuilder::YamlBuilder()
{

}
ActiveYaml::YamlObjectPtr YamlBuilder::operator()(const QString &value) const
{
    return YamlObject::string(value);
}

YamlObjectPtr YamlBuilder::operator ()(const char *value) const
{
    return YamlObject::string(value);
}

ActiveYaml::YamlObjectPtr YamlBuilder::operator()(int value) const
{
    return YamlObject::integer(value);
}

ActiveYaml::YamlObjectPtr YamlBuilder::operator ()(double value) const
{
    return YamlObject::float_(value);
}

YamlObjectPtr YamlBuilder::operator ()(bool value) const
{
    return YamlObject::boolean(value);
}

YamlObjectPtr YamlBuilder::operator ()(const YamlObjectPtr &value) const
{
    return value;
}

YamlObjectPtr YamlBuilder::object(const std::vector<YamlObjectKeyPair> &args) const
{
    auto y = YamlObject::object();
    for (auto i : args) {
        y->insert(i.key(), i.value());
    }
    return y;
}

