#ifndef YAMLOBJECT_H
#define YAMLOBJECT_H

#include <memory>
#include <functional>
#include <memory>
#include <QVariant>
#include <QFile>
#include <QList>

namespace ActiveYaml
{

class YamlObject;
class YamlPath;
typedef std::shared_ptr<YamlObject> YamlObjectPtr;
typedef std::shared_ptr<const YamlObject> YamlObjectConstPtr;

class YamlObject : std::enable_shared_from_this<YamlObject>
{
public:
    class Iterator;
    class ConstIterator;

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

    // for integer
    int integerValue() const;

    // for float
    double floatValue() const;

    // for boolean
    bool booleanValue() const;

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
    Iterator begin() const;
    Iterator end() const;
    size_t count() const;

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
    bool isCollection() const;

    virtual QString toString() const;

private:
    explicit YamlObject();
    static YamlObjectPtr create();

    void assertType(Type type) const;
    void assertTypeImpl(Type type) const;
    void assertIsCollection() const;
    void assertIsCollectionImpl() const;

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

public:
    class Iterator {
    public:
        Iterator(const YamlObjectConstPtr& object, QList<YamlObjectPtr>::const_iterator iterator) :
            m_object(object),
            m_iterator(iterator)
        {
            m_iterator = m_object->m_variableValue->list.begin();
        }

        YamlObjectPtr operator *() const {
            return value();
        }

        Iterator operator ++() {
            m_iterator++;
            return *this;
        }

        Iterator operator ++(int) {
            auto oldValue = *this;
            ++m_iterator;
            return oldValue;
        }

        bool operator !=(const Iterator& itr) const {
            return itr.m_iterator != m_iterator;
        }

        bool operator ==(const Iterator& itr) const {
            return itr.m_iterator != m_iterator;
        }

        YamlObjectPtr value() const {
            if (m_object->type() == YamlObject::TypeObject) {
                return m_object->m_variableValue->map[*m_iterator];
            } else {
                return *m_iterator;
            }
        }

        YamlObjectPtr key() const {
            if (m_object->type() == YamlObject::TypeObject) {
                return *m_iterator;
            }
            // TODO 例外処理
        }

    private:
        YamlObjectConstPtr m_object;
        QList<YamlObjectPtr>::const_iterator m_iterator;
    };
};

inline void YamlObject::assertType(Type type) const
{
#ifdef DEBUG
        assertTypeImpl(type);
#endif
}

inline void YamlObject::assertIsCollection() const
{
#ifdef DEBUG
        assertIsCollectionImpl();
#endif
}

inline int YamlObject::integerValue() const
{
    assertType(TypeInteger);
    return m_basicValue.intValue;
}

inline double YamlObject::floatValue() const
{
    assertType(TypeFloat);
    return m_basicValue.floatValue;
}

inline bool YamlObject::booleanValue() const
{
    assertType(TypeBoolean);
    return m_basicValue.boolValue;
}

inline QString YamlObject::stringValue() const
{
    assertType(TypeString);
    return m_stringValue;
}

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
