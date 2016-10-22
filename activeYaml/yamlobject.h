#ifndef YAMLOBJECT_H
#define YAMLOBJECT_H

#include <QVariant>
#include <QFile>
#include <memory>
#include <functional>
#include <memory>

namespace ActiveYaml
{

class YamlObject;
class YamlPath;
typedef std::shared_ptr<YamlObject> YamlObjectPtr;

class YamlObject : std::enable_shared_from_this<YamlObject>
{
public:
    enum Type{
        TypeNone = 0,
        TypeObject,
        TypeArray,
        TypeInteger,
        TypeFloat,
        TypeString,
        TypeBoolean,
        TypeNull,
    };

    ~YamlObject();

    static YamlObjectPtr integer(int n);
    static YamlObjectPtr boolean(bool value);
    static YamlObjectPtr string(const QString &text);
    static YamlObjectPtr object();
    static YamlObjectPtr array();
    static YamlObjectPtr null();
    static YamlObjectPtr float_(double value);
    static QString typeToName(Type type);

    QString dump() const;
    QVariant toQVariant() const;

    // for integer
    int integerValue() const;

    // for string
    QString stringValue() const;

    // for object
    YamlObjectPtr operator [](const YamlObjectPtr &key) const;
    YamlObjectPtr operator [](const QString &key) const;
    YamlObjectPtr value(const YamlObjectPtr &key) const;
    YamlObjectPtr value(const QString &key) const;
    YamlObjectPtr insert(const YamlObjectPtr &key, const YamlObjectPtr& value);
    YamlObjectPtr insert(const QString &key, const YamlObjectPtr& value);
    YamlObjectPtr removeAt(const YamlObjectPtr &key);
    YamlObjectPtr removeAt(const QString &key);
    bool contains(const YamlObjectPtr &key) const;
    bool contains(const QString &key) const;

    // for array
    void append(YamlObjectPtr &object);
    YamlObjectPtr insert(int index, const YamlObjectPtr& value);
    YamlObjectPtr removeAt(int index);
    QList<YamlObjectPtr> arrayValue() const;
    void forEach(std::function<void(YamlObjectPtr)> callback) const;

    // for collection
    YamlObjectPtr remove(const YamlObjectPtr& value);

    // for general
    Type type() const;
    uint getHash(uint seed = 0) const;
    bool operator ==(const YamlObject &another) const;
    YamlObjectPtr findByPath(const YamlPath &path) const;

    bool isNull() const;
    bool isObject() const;
    bool isArray() const;
    bool isString() const;
    bool isInteger() const;

    virtual QString toString() const;

private:
    explicit YamlObject();
    static YamlObjectPtr create();
    void emitYaml(void* emitter) const;


private:
    Type m_type;

    union {
        bool boolValue;
        qint64 intValue;
        qreal floatValue;
    } m_basicValue;

    QString m_stringValue;

    struct VariableValue {
        QList<YamlObjectPtr> list;
        QHash<YamlObjectPtr, YamlObjectPtr> map;
    };
    std::unique_ptr<VariableValue> m_variableValue;

    YamlObjectPtr m_parent;
};
}

inline uint qHash(const ActiveYaml::YamlObjectPtr &yamlObject, uint seed = 0)
{
    return yamlObject->getHash(seed);
}

inline bool operator==(const ActiveYaml::YamlObjectPtr &lhs, const ActiveYaml::YamlObjectPtr &rhs)
{
    return *lhs == *rhs;
}


#endif // YAMLOBJECT_H
