#include "yamlpath.h"

#include <QStringList>

#include "activeyamlexception.h"

using namespace ActiveYaml;


YamlPathElement YamlPathElement::arrayIndex(int n)
{
    YamlPathElement element;
    element.m_type = YamlPathType::ArrayIndex;
    element.m_index = n;
    return element;
}

YamlPathElement YamlPathElement::objectProperty(const QString name)
{
    YamlPathElement element;
    element.m_type = YamlPathType::ObjectProperty;
    element.m_name = name;
    return element;
}

YamlPathElement YamlPathElement::propertyOrIndex(QString name)
{
    YamlPathElement element;
    element.m_type = YamlPathType::PropertyOrIndex;
    element.m_name = name;
    return element;
}

YamlPathElement YamlPathElement::root()
{
    YamlPathElement element;
    element.m_type = YamlPathType::Root;
    return element;
}

YamlPathElement YamlPathElement::all()
{
    YamlPathElement element;
    element.m_type = YamlPathType::All;
    return element;
}

QString YamlPathElement::property() const
{
    switch (m_type) {
    case YamlPathType::ObjectProperty:
    case YamlPathType::PropertyOrIndex:
        return m_name;

    default:
        throw ActiveYamlTypeException("");
    }
}

int YamlPathElement::index() const
{
    switch (m_type) {
    case YamlPathType::ArrayIndex:
    case YamlPathType::PropertyOrIndex:
        return m_index;

    default:
        throw ActiveYamlTypeException("");
    }
}

YamlPath::YamlPath(const YamlPathElementList &elements)
{
    m_elements = elements;
}

YamlPath::YamlPath()
{

}

YamlPath YamlPath::parse(const QString &pathText)
{
    if (pathText == "/") {
        return YamlPath(YamlPathElementList{YamlPathElement::root()});
    }

    if (pathText == "") {
        return YamlPath();
    }

    QStringList elementTexts = pathText.split("/");
    std::vector<YamlPathElement> elements;

    if (elementTexts.isEmpty()) {
        return YamlPath();
    }

    auto i = elementTexts.begin();
    if ((*i).isEmpty()) {
        elements.push_back(YamlPathElement::root());
        i++;
    }

    for (; i != elementTexts.end(); i++) {
        if (*i == "") {

        } else if (*i == "*") {
            elements.push_back(YamlPathElement::all());
        } else if ((*i).contains("*")) {

        } else if ((*i) == "..") {

        } else {
            elements.push_back(YamlPathElement::propertyOrIndex(*i));
        }
    }

    return YamlPath(elements);
}

YamlPath YamlPath::dig(int count) const
{
    if (m_elements.size() < count || count < 0) {
        throw OutOfRangeException("");
    }
    std::vector<YamlPathElement> elements(m_elements.begin() + count, m_elements.end());
    return YamlPath(elements);
}

bool YamlPath::isEmpty() const
{
    return m_elements.empty();
}
