#include "yamlobject.h"

#include <exception>
#include <QDebug>
#include <yaml.h>
#include <QVector>
#include <QStringBuilder>

#include "activeyamlexception.h"
#include "yamlpath.h"

using namespace ActiveYaml;

bool YamlObject::isDebugOutputEnabled = false;

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

QString YamlObject::stringValue() const
{
    if (m_type != TypeString) {
        throw ActiveYamlTypeException("");
    }
    return m_stringValue;
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
    if (m_type != TypeObject) {
        throw ActiveYamlTypeException("");
    }
    const QHash<YamlObjectPtr, YamlObjectPtr> &map = m_variableValue->map;
    return map.value(key);
}

YamlObjectPtr YamlObject::value(const QString &key) const
{
    return value(YamlObjectPtr(YamlObject::string(key)));
}

YamlObjectPtr YamlObject::insert(const YamlObjectPtr &key, const YamlObjectPtr &value)
{
    if (m_type != TypeObject) {
        throw ActiveYamlTypeException("");
    }

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
    if (m_type != TypeObject) {
        throw ActiveYamlTypeException("");
    }
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
    if (m_type != TypeArray) {
        throw ActiveYamlException("");
    }
    m_variableValue->list.insert(index, value);
    value->m_parent = shared_from_this();
    return value;
}

void YamlObject::append(YamlObjectPtr &object)
{
    if (m_type != TypeArray) {
        throw ActiveYamlException("");
    }
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

// parse
YamlObjectPtr YamlObject::fromFile(const QString &fileName)
{
    auto stdFileName = fileName.toStdString();
    FILE *file = fopen(stdFileName.c_str(), "r");

    if (!file) {
        throw new std::exception((std::string() + "cannot open file " + stdFileName).c_str());
    }

    yaml_parser_t parser;
    yaml_parser_initialize(&parser);
    yaml_parser_set_input_file(&parser, file);

    try{
        return parse(&parser);
        yaml_parser_delete(&parser);
        fclose(file);
    } catch (std::exception &e) {
        yaml_parser_delete(&parser);
        fclose(file);
        throw;
    }
}

int yaml_read_handler(void *data, unsigned char *buffer, size_t size, size_t *size_read)
{
    QFile *file = (QFile *)data;

    *size_read = file->read((char *)buffer, size);

    return 1;
}

YamlObjectPtr YamlObject::fromFile(QFile &file)
{
    bool needsOpen = !file.isOpen();
    if (needsOpen) {
        if (!file.open(QFile::ReadOnly)) {
            qDebug() << file.errorString();
            throw std::exception((std::string() + "cannot open file " + file.fileName().toStdString()).c_str());
        }
    }

    yaml_parser_t parser;
    yaml_parser_initialize(&parser);
    yaml_parser_set_input(&parser, &yaml_read_handler, &file);

    try{
        YamlObjectPtr ret = parse(&parser);
        yaml_parser_delete(&parser);
        if (needsOpen) {
            file.close();
        }
        return ret;
    } catch (std::exception &e) {
        yaml_parser_delete(&parser);
        if (needsOpen) {
            file.close();
        }
        throw;
    }
}

void exec_event(yaml_emitter_t &emitter, yaml_event_t &event)
{
    if (!yaml_emitter_emit(&emitter, &event)) {
        throw ActiveYamlEmitterException("");
    }
}

void stream_start_event(yaml_emitter_t &emitter)
{
    yaml_event_t event;
    if (!yaml_stream_start_event_initialize(&event, YAML_UTF8_ENCODING)) {
        throw ActiveYamlEmitterException("");
    }
    exec_event(emitter, event);
}

void document_start_event(yaml_emitter_t &emitter)
{
    yaml_event_t event;
    if (!yaml_document_start_event_initialize(&event, 0, 0, 0, 0)) {
        throw ActiveYamlEmitterException("");
    }
    exec_event(emitter, event);
}

void document_end_event(yaml_emitter_t &emitter)
{
    yaml_event_t event;
    if (!yaml_document_end_event_initialize(&event, 0)) {
        throw ActiveYamlEmitterException("");
    }
    exec_event(emitter, event);
}

void stream_end_event(yaml_emitter_t &emitter)
{
    yaml_event_t event;
    if (!yaml_stream_end_event_initialize(&event)) {
        throw ActiveYamlEmitterException("");
    }
    exec_event(emitter, event);
}

int write_handler(void *ext, unsigned char *buffer, size_t size) {
    QString *output = (QString *)ext;
    output->append(QString::fromUtf8((char*)buffer, (int)size));
    bool error = false;
    return error ? 0 : 1;
}

QString YamlObject::dump() const
{
    yaml_emitter_t emitter;
    yaml_emitter_initialize(&emitter);
    QString outputString;
    yaml_emitter_set_output(&emitter, write_handler, (void *)&outputString);

    try {
        stream_start_event(emitter);
        document_start_event(emitter);

        this->emitYaml(&emitter);

        document_end_event(emitter);
        stream_end_event(emitter);
        yaml_emitter_delete(&emitter);
    }
    catch (ActiveYamlEmitterException &ex)
    {
        yaml_emitter_delete(&emitter);
        throw;
    }
    return outputString;
}

QVariant YamlObject::toQVariant() const
{
    switch (this->type()) {
    case TypeNone:
        throw ActiveYamlTypeException("");

    case TypeObject:
    {
        QVariantMap map;
        for (auto i = m_variableValue->map.constBegin(); i != m_variableValue->map.constEnd(); i++) {
            map.insert(i.key()->toString(), i.value()->toQVariant());
        }
        return map;
    }

    case TypeArray:
    {
        QVariantList list;
        for (auto i : m_variableValue->list) {
            list.append(i->toQVariant());
        }
        return QVariant(list);
    }

    case TypeInteger:
        return QVariant(m_basicValue.intValue);

    case TypeFloat:
        return QVariant(m_basicValue.floatValue);

    case TypeString:
        return QVariant(m_stringValue);

    case TypeBoolean:
        return QVariant(m_basicValue.boolValue);

    case TypeNull:
        return QVariant();
    }
}

int YamlObject::integerValue() const
{
    if (m_type != TypeInteger) {
        throw ActiveYamlTypeException("");
    }
    return m_basicValue.intValue;
}

void YamlObject::emitYaml(void *emitter) const
{
    yaml_emitter_t *_emitter = (yaml_emitter_t *)emitter;
    yaml_event_t event;
    yaml_char_t *tag = (yaml_char_t *)"";

    switch (this->type()) {
    case TypeNone:
        break;

    case TypeObject:
    {
        yaml_mapping_start_event_initialize(&event, 0, 0, 1, YAML_BLOCK_MAPPING_STYLE);
        exec_event(*_emitter, event);

        for (YamlObjectPtr i : this->m_variableValue->list) {
            i->emitYaml(emitter);
            this->m_variableValue->map[i]->emitYaml(emitter);
        }

        yaml_mapping_end_event_initialize(&event);
        exec_event(*_emitter, event);
    }
        break;

    case TypeArray:
        yaml_sequence_start_event_initialize(&event, 0, 0, 1, YAML_BLOCK_SEQUENCE_STYLE);
        exec_event(*_emitter, event);

        for (YamlObjectPtr i : this->m_variableValue->list) {
            i->emitYaml(emitter);
        }

        yaml_sequence_end_event_initialize(&event);
        exec_event(*_emitter, event);

        break;

    case TypeInteger:
    {
        std::string value = std::to_string(this->m_basicValue.intValue);
        yaml_scalar_event_initialize(&event, 0, 0,
                                     (yaml_char_t *)value.c_str(), value.length(), 1, 0,
                                     YAML_PLAIN_SCALAR_STYLE);
        exec_event(*_emitter, event);
    }
        break;

    case TypeFloat:
    {
        std::string value = std::to_string(this->m_basicValue.floatValue);
        yaml_scalar_event_initialize(&event, 0, 0,
                                     (yaml_char_t *)value.c_str(), value.length(), 1, 0,
                                     YAML_PLAIN_SCALAR_STYLE);
    }
        break;

    case TypeString:
    {
        auto bytes = this->m_stringValue.toUtf8();
        yaml_scalar_event_initialize(&event, 0, 0,
                                     (yaml_char_t *)bytes.data(), bytes.size(), 1, 1,
                                     YAML_DOUBLE_QUOTED_SCALAR_STYLE);
        exec_event(*_emitter, event);
    }
        break;

    case TypeBoolean:
    {
        if (this->m_basicValue.boolValue) {
            yaml_scalar_event_initialize(&event, 0, 0,
                                         (yaml_char_t *)"true", 5, 1, 0,
                                         YAML_PLAIN_SCALAR_STYLE);
        } else {
            yaml_scalar_event_initialize(&event, 0, 0,
                                         (yaml_char_t *)"false", 6, 1, 0,
                                         YAML_PLAIN_SCALAR_STYLE);
        }
        exec_event(*_emitter, event);
    }
        break;

    case TypeNull:
        yaml_scalar_event_initialize(&event, 0, 0,
                                     (yaml_char_t *)"null", 5, 1, 0,
                                     YAML_PLAIN_SCALAR_STYLE);
        exec_event(*_emitter, event);
        break;
    }
}

bool YamlObject::isIntegerString(const QString &string)
{
    static QRegExp isInteger("^\\d+$");
    return isInteger.exactMatch(string);
}

bool YamlObject::isFloatString(const QString &string)
{
    static QRegExp isFloat("^\\d+\\.\\d+");
    return isFloat.exactMatch(string);
}

YamlObjectPtr YamlObject::parse(void *parser_)
{
    yaml_parser_t* parser = (yaml_parser_t*)parser_;
    bool is_done = false;
    yaml_event_t event;
    YamlObjectPtr rootObject = YamlObjectPtr(0);
    QVector<YamlObjectPtr> objectStack;
    QVector<YamlObjectPtr> mapKeys;

    while (!is_done) {
        if (!yaml_parser_parse(parser, &event)) {
            throw new std::exception("parse error");
        }

        switch (event.type) {
        case YAML_NO_EVENT:
            if (isDebugOutputEnabled) qDebug() << "YAML_NO_EVENT";
            break;

        case YAML_STREAM_START_EVENT:
            if (isDebugOutputEnabled) qDebug() << "YAML_STREAM_START_EVENT";
            break;

        case YAML_STREAM_END_EVENT:
            if (isDebugOutputEnabled) qDebug() << "YAML_STREAM_END_EVENT";
            break;

        case YAML_DOCUMENT_START_EVENT:
            if (isDebugOutputEnabled) qDebug() << "YAML_DOCUMENT_START_EVENT";
            break;
        case YAML_DOCUMENT_END_EVENT:
            if (isDebugOutputEnabled) qDebug() << "YAML_DOCUMENT_END_EVENT";
            is_done = true;
            break;

        case YAML_ALIAS_EVENT:
            if (isDebugOutputEnabled) qDebug() << "YAML_ALIAS_EVENT";
            break;

        case YAML_SCALAR_EVENT:
        {
            QString value = QString::fromUtf8((char *)event.data.scalar.value);
            QString tag = QString::fromUtf8((char *)event.data.scalar.tag);

            if (isDebugOutputEnabled) {
                        qDebug() << "YAML_SCALAR_EVENT " << tag << " -> " << value;
                        qDebug() << event.start_mark.line << " " << event.end_mark.line;
            }

            YamlObjectPtr yamlValue(0);
            const yaml_scalar_style_t &style = event.data.scalar.style;
            if (isIntegerString(value) && style != YAML_PLAIN_SCALAR_STYLE) {
                yamlValue = YamlObjectPtr(YamlObject::integer(value.toInt()));
            } else if (isFloatString(value) && style != YAML_PLAIN_SCALAR_STYLE) {
                yamlValue = YamlObjectPtr(YamlObject::float_(value.toDouble()));
            } else if (value == "true") {
                yamlValue = YamlObjectPtr(YamlObject::boolean(true));
            } else if (value == "false") {
                yamlValue = YamlObjectPtr(YamlObject::boolean(false));
            } else if (value == "null") {
                yamlValue = YamlObjectPtr(YamlObject::null());
            } else {
                yamlValue = YamlObjectPtr(YamlObject::string(value));
            }

            if (!objectStack.empty()) {
                switch (objectStack.last()->type()) {
                case YamlObject::TypeArray:
                    objectStack.last()->append(yamlValue);
                    break;

                case YamlObject::TypeObject:
                    if (!mapKeys.last()) {
                        mapKeys.last() = yamlValue;
                    } else {
                        YamlObjectPtr key = mapKeys.last();
                        objectStack.last()->insert(key, yamlValue);
                        mapKeys.last() = YamlObjectPtr();
                    }
                    break;
                }
            } else {
                rootObject = yamlValue;
            }
        }
            break;

        case YAML_SEQUENCE_START_EVENT:
        {
            if (isDebugOutputEnabled) qDebug() << "YAML_SEQUENCE_START_EVENT";

            auto yamlValue = YamlObjectPtr(YamlObject::array());
            if (!rootObject) {
                rootObject = yamlValue;
            }
            if (!objectStack.empty()) {
                switch (objectStack.last()->type()) {
                case YamlObject::TypeArray:
                    objectStack.last()->append(yamlValue);
                    break;

                case YamlObject::TypeObject:
                    if (!mapKeys.last()) {
                        // keyに配列は指定できない想定
                        throw ActiveYamlTypeException("");
                    } else {
                        YamlObjectPtr key = mapKeys.last();
                        objectStack.last()->insert(key, yamlValue);
                        mapKeys.last() = YamlObjectPtr();
                    }
                    break;
                }
            }
            objectStack.push_back(yamlValue);
        }
            break;

        case YAML_SEQUENCE_END_EVENT:
            if (isDebugOutputEnabled) qDebug() << "YAML_SEQUENCE_END_EVENT";

            // TODO assertion
            objectStack.pop_back();
            break;

        case YAML_MAPPING_START_EVENT:
        {
            if (isDebugOutputEnabled) qDebug() << "YAML_MAPPING_START_EVENT";

            auto yamlValue = YamlObjectPtr(YamlObject::object());
            if (!rootObject) {
                rootObject = yamlValue;
            }
            if (!objectStack.empty()) {
                switch (objectStack.last()->type()) {
                case YamlObject::TypeArray:
                    objectStack.last()->append(yamlValue);
                    break;

                case YamlObject::TypeObject:
                    if (!mapKeys.last()) {
                        // keyにobjectは指定できない想定
                        throw ActiveYamlTypeException("");
                    } else {
                        YamlObjectPtr key = mapKeys.last();
                        objectStack.last()->insert(key, yamlValue);
                        mapKeys.last() = YamlObjectPtr();
                    }
                    break;
                }
            }
            mapKeys.push_back(YamlObjectPtr(0));
            objectStack.push_back(yamlValue);
        }
            break;

        case YAML_MAPPING_END_EVENT:
            if (isDebugOutputEnabled) qDebug() << "YAML_MAPPING_END_EVENT";

            // TODO assertion
            objectStack.pop_back();
            mapKeys.pop_back();
            break;
        }
    }

    return rootObject;
}
