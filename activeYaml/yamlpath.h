#ifndef YAMLPATH_H
#define YAMLPATH_H

#include <QString>
#include <vector>

namespace ActiveYaml
{
enum class YamlPathType{
    ArrayIndex,
    ObjectProperty,
    PropertyOrIndex,
    Reverse,
    Pattern,
    All,
    Root,
};

class YamlPathElement
{
    YamlPathElement() {}

public:
    YamlPathType type() const { return m_type; }

    static YamlPathElement arrayIndex(int n);
    static YamlPathElement objectProperty(const QString name);
    static YamlPathElement propertyOrIndex(QString name);
    static YamlPathElement all();
    static YamlPathElement root();

    QString property() const;
    int index() const;

private:
    YamlPathType m_type;
    QString m_name;
    int m_index;
};

typedef std::vector<YamlPathElement> YamlPathElementList;

class YamlPath
{
    YamlPath(const YamlPathElementList &elements);

public:
    YamlPath();

    static YamlPath parse(const QString& path);

    YamlPath dig(int count = 1) const;

    YamlPathElement elementAt(int index) const { return m_elements.at(index); }
    YamlPathElement first() const { return m_elements.front(); }
    bool isEmpty() const;
    int size() const { return m_elements.size(); }
    
private:
    YamlPathElementList m_elements;
};
}

#endif // YAMLPATH_H
