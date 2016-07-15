#ifndef YAMLOBJECT_H
#define YAMLOBJECT_H

#include <QVariant>
#include <QSharedPointer>
#include <QFile>
#include <memory>
#include <functional>

class YamlObject;
typedef QSharedPointer<YamlObject> YamlObjectPtr;

class YamlObject
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

    static YamlObject* integer(int n);
    static YamlObject* boolean(bool value);
    static YamlObject* string(const QString &text);
    static YamlObject* object();
    static YamlObject* array();
    static YamlObject* null();
    static YamlObject* float_(double value);
    static QString typeToName(Type type);
    static YamlObjectPtr fromFile(const QString &fileName);
    static YamlObjectPtr fromFile(QFile &file);

    static bool isDebugOutputEnabled;

    QString dump() const;
    QVariant toQVariant() const;

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

    virtual QString toString() const;

private:
    explicit YamlObject();
    static YamlObjectPtr parse(void* parser);
    void emitYaml(void* emitter) const;

    static bool isIntegerString(const QString &string);
    static bool isFloatString(const QString &string);

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
};

inline uint qHash(const YamlObjectPtr &yamlObject, uint seed = 0)
{
    return yamlObject->getHash(seed);
}

inline bool operator==(const YamlObjectPtr &lhs, const YamlObjectPtr &rhs)
{
    return *lhs == *rhs;
}

#endif // YAMLOBJECT_H
