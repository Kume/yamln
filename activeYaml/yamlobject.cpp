#include "yamlobject.h"

#include <exception>
#include <QDebug>
#include <QVector>
#include <QStringBuilder>

#include "yamlpath.h"
#include "activeyamlexception.h"

using namespace ActiveYaml;

YamlObject::YamlObject()
{

}

YamlObjectPtr YamlObject::create()
{
    struct impl : YamlObject {
        impl() : YamlObject() {}
    };

    auto ptr = std::make_shared<impl>();
    return std::move(ptr);
}

void YamlObject::assertTypeImpl(Type type) const
{
    if (m_type != type) {
        throw ActiveYamlTypeException("");
    }
}

YamlObject::~YamlObject()
{

}

YamlObjectPtr YamlObject::integer(int n)
{
    auto object = create();
    object->m_type = TypeInteger;
    object->m_basicValue.intValue = n;
    return object;
}

YamlObjectPtr YamlObject::boolean(bool value)
{
    auto object = create();
    object->m_type = TypeBoolean;
    object->m_basicValue.boolValue = value;
    return object;
}

YamlObjectPtr YamlObject::string(const QString &text)
{
    auto object = create();
    object->m_type = TypeString;
    object->m_stringValue = text;
    return object;
}

YamlObjectPtr YamlObject::array()
{
    auto object = create();
    object->m_type = TypeArray;
    object->m_variableValue = std::unique_ptr<VariableValue>(new VariableValue());
    return object;
}

YamlObjectPtr YamlObject::object()
{
    auto object = create();
    object->m_type = TypeObject;
    object->m_variableValue = std::unique_ptr<VariableValue>(new VariableValue());
    return object;
}

YamlObjectPtr YamlObject::null()
{
    auto object = create();
    object->m_type = TypeNull;
    return object;
}

YamlObjectPtr YamlObject::float_(double value)
{
    auto object = create();
    object->m_type = TypeFloat;
    object->m_basicValue.floatValue = value;
    return object;
}

QString YamlObject::typeToName(Type type)
{
    switch (type) {
    case TypeNone:
        return "none";

    case TypeObject:
        return "object";

    case TypeArray:
        return "array";

    case TypeInteger:
        return "integer";

    case TypeFloat:
        return "float";

    case TypeString:
        return "string";

    case TypeBoolean:
        return "boolean";

    case TypeNull:
        return "null";
    }
    throw ActiveYamlTypeException("");
}

YamlObjectPtr YamlObject::operator [](const YamlObjectPtr &key) const
{
    return value(key);
}

YamlObjectPtr YamlObject::operator [](const QString &key) const
{
    return value(key);
}

YamlObjectPtr YamlObject::value(const YamlObjectPtr &key) const
{
    assertType(TypeObject);
    const QHash<YamlObjectPtr, YamlObjectPtr> &map = m_variableValue->map;
    return map.value(key);
}

YamlObjectPtr YamlObject::value(const QString &key) const
{
    return value(YamlObjectPtr(YamlObject::string(key)));
}

YamlObjectPtr YamlObject::insert(const YamlObjectPtr &key, const YamlObjectPtr &value)
{
    assertType(TypeObject);

    if (!m_variableValue->map.contains(key)) {
        m_variableValue->list.append(key);
        key->m_parent = shared_from_this();
    } else {
        m_variableValue->map[key]->m_parent.reset();
    }

    value->m_parent = shared_from_this();
    return m_variableValue->map[key] = value;
}

YamlObjectPtr YamlObject::insert(const QString &key, const YamlObjectPtr &value)
{
    return insert(YamlObjectPtr(YamlObject::string(key)), value);
}

YamlObjectPtr YamlObject::removeAt(const YamlObjectPtr &key)
{
    if (m_type != TypeObject) {
        throw ActiveYamlTypeException("");
    }

    if (!m_variableValue->map.contains(key)) {
        YamlObjectPtr ret = m_variableValue->map[key];
        m_variableValue->map.remove(key);
        m_variableValue->list.removeOne(key);
        return ret;
    } else {
        return YamlObjectPtr(0);
    }
}

YamlObjectPtr YamlObject::removeAt(const QString &key)
{
    return removeAt(YamlObjectPtr(YamlObject::string(key)));
}

bool YamlObject::contains(const YamlObjectPtr &key) const
{
    assertType(TypeObject);
    const QHash<YamlObjectPtr, YamlObjectPtr> &map = m_variableValue->map;
    return map.contains(key);
}

bool YamlObject::contains(const QString &key) const
{
    return contains(YamlObjectPtr(YamlObject::string(key)));
}

// for array
YamlObjectPtr YamlObject::insert(int index, const YamlObjectPtr &value)
{
    assertType(TypeArray);
    m_variableValue->list.insert(index, value);
    value->m_parent = shared_from_this();
    return value;
}

void YamlObject::append(YamlObjectPtr &object)
{
    assertType(TypeArray);
    m_variableValue->list.append(object);
}

void YamlObject::forEach(std::function<void (YamlObjectPtr)> callback) const
{
    for (auto i : m_variableValue->list) {
        callback(i);
    }
}

// for collection
YamlObjectPtr YamlObject::remove(const YamlObjectPtr &value)
{
    switch (m_type) {
    case TypeObject:
        // TODO
        break;

    case TypeArray:
        {
            int index = m_variableValue->list.indexOf(value);
            if (index >= 0) {
                m_variableValue->list.removeAt(index);
            }
            break;
        }

    default:
        throw ActiveYamlTypeException("");
    }
}

YamlObject::Iterator YamlObject::begin() const
{
    return Iterator(shared_from_this(), m_variableValue->list.constBegin());
}

YamlObject::Iterator YamlObject::end() const
{
    return Iterator(shared_from_this(), m_variableValue->list.constEnd());
}

// for general
YamlObject::Type YamlObject::type() const
{
    return m_type;
}

uint YamlObject::getHash(uint seed) const
{
    switch (type()) {
    case TypeNone:
        return 0;

    case TypeObject:
        // Hashのキーにはならないはず。。
        throw ActiveYamlTypeException("");

    case TypeArray:
        // Hashのキーにはならないはず。。
        throw ActiveYamlTypeException("");

    case TypeInteger:
        return qHash(this->m_basicValue.intValue, seed);

    case TypeFloat:
        return qHash(this->m_basicValue.floatValue, seed);

    case TypeString:
        return qHash(this->m_stringValue, seed);

    case TypeBoolean:
        return this->m_basicValue.boolValue ? 2 : 3;

    case TypeNull:
        return 1;
    }

    throw ActiveYamlTypeException("");
}

bool YamlObject::operator ==(const YamlObject &another) const
{
    if (this->type() != another.type()) return false;

    switch (type()) {
    case TypeNone:
        return true;

    case TypeObject:
    {
        QList<YamlObjectPtr> &thisList = this->m_variableValue->list;
        QList<YamlObjectPtr> &anotherList = another.m_variableValue->list;
        int size = thisList.size();
        if (size != anotherList.size()) return false;
        // まずはキーの一致を調べる
        {
            auto thisI = thisList.constBegin();
            auto anotherI = anotherList.constBegin();
            auto thisEnd = thisList.constEnd();
            while (thisI != thisEnd) {
                if (!(**thisI == **anotherI)) {
                    return false;
                }
                ++thisI;
                ++anotherI;
            }
        }
        {
            auto thisI = this->m_variableValue->map.constBegin();
            auto anotherI = this->m_variableValue->map.constBegin();
            auto thisEnd = this->m_variableValue->map.constEnd();
            while (thisI != thisEnd) {
                if (!(*(thisI.value()) == *(anotherI.value()))) {
                    return false;
                }
                ++thisI;
                ++anotherI;
            }
        }
        return true;
    }

    case TypeArray:
    {
        QList<YamlObjectPtr> &thisList = this->m_variableValue->list;
        QList<YamlObjectPtr> &anotherList = another.m_variableValue->list;
        int size = thisList.size();
        if (size != anotherList.size()) return false;
        auto thisI = thisList.constBegin();
        auto anotherI = anotherList.constBegin();
        auto thisEnd = thisList.constEnd();
        while (thisI != thisEnd) {
            if (!(**thisI == **anotherI)) {
                return false;
            }
            ++thisI;
            ++anotherI;
        }
    }

    case TypeInteger:
        return this->m_basicValue.intValue == another.m_basicValue.intValue;

    case TypeFloat:
        return this->m_basicValue.floatValue == another.m_basicValue.floatValue;

    case TypeString:
        return this->m_stringValue == another.m_stringValue;

    case TypeBoolean:
        return this->m_basicValue.boolValue == another.m_basicValue.boolValue;

    case TypeNull:
        return true;

    default:
        throw ActiveYamlTypeException("");
    }
}

YamlObjectPtr YamlObject::findByPath(const YamlPath &path) const
{
    switch(m_type) {
    case TypeObject:


    case TypeArray:

    default:
        if(path.isEmpty()) {
            // return sharedFromThis();
        }
    }

    // TODO 後で消す
    return YamlObjectPtr();
}

bool YamlObject::isNull() const
{
    return m_type == TypeNull;
}

bool YamlObject::isObject() const
{
    return m_type == TypeObject;
}

bool YamlObject::isArray() const
{
    return m_type == TypeArray;
}

bool YamlObject::isString() const
{
    return m_type == TypeString;
}

bool YamlObject::isInteger() const
{
    return m_type == TypeInteger;
}

QString YamlObject::toString() const
{
    switch (this->type()) {
    case TypeNone:
        throw ActiveYamlTypeException("");

    case TypeObject:
        return "{}"; // TODO

    case TypeArray:
        return "[]"; // TODO

    case TypeInteger:
        return QString::number(m_basicValue.intValue);

    case TypeFloat:
        return QString::number(m_basicValue.floatValue);

    case TypeString:
        return m_stringValue;

    case TypeBoolean:
        return m_basicValue.boolValue ? "true" : "false";

    case TypeNull:
        return "null";
    }
}
