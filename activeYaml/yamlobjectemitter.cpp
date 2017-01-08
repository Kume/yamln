#include "yamlobjectemitter.h"

#include <yaml.h>
#include "activeyamlexception.h"

using namespace ActiveYaml;

YamlObjectEmitter::YamlObjectEmitter()
{

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

QString YamlObjectEmitter::dump(const YamlObjectPtr &yamlObject)
{
    yaml_emitter_t emitter;
    yaml_emitter_initialize(&emitter);
    QString outputString;
    yaml_emitter_set_output(&emitter, write_handler, (void *)&outputString);

    try {
        stream_start_event(emitter);
        document_start_event(emitter);

        emitYaml(yamlObject, &emitter);

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


QVariant YamlObjectEmitter::toQVariant(const YamlObjectPtr &yamlObject)
{
    switch (yamlObject->type()) {
    case YamlObject::TypeNone:
        throw ActiveYamlTypeException("");

    case YamlObject::TypeObject:
    {
        QVariantMap map;
        for (auto i = yamlObject->begin(); i != yamlObject->end(); ++i) {
            map.insert(i.key()->toString(), toQVariant(i.value()));
        }
        return map;
    }

    case YamlObject::TypeArray:
    {
        QVariantList list;
        for (auto i : *yamlObject) {
            list.append(toQVariant(i));
        }
        return QVariant(list);
    }

    case YamlObject::TypeInteger:
        return QVariant(yamlObject->integerValue());

    case YamlObject::TypeFloat:
        return QVariant(yamlObject->floatValue());

    case YamlObject::TypeString:
        return QVariant(yamlObject->stringValue());

    case YamlObject::TypeBoolean:
        return QVariant(yamlObject->booleanValue());

    case YamlObject::TypeNull:
        return QVariant();
    }
}

void YamlObjectEmitter::emitYaml(const YamlObjectPtr &yamlObject, void *emitter)
{
    yaml_emitter_t *_emitter = (yaml_emitter_t *)emitter;
    yaml_event_t event;
    yaml_char_t *tag = (yaml_char_t *)"";

    switch (yamlObject->type()) {
    case YamlObject::TypeNone:
        break;

    case YamlObject::TypeObject:
    {
        yaml_mapping_start_event_initialize(&event, 0, 0, 1, YAML_BLOCK_MAPPING_STYLE);
        exec_event(*_emitter, event);

        for (auto i = yamlObject->begin(); i != yamlObject->end(); ++i) {
            emitYaml(i.key(), emitter);
            emitYaml(i.value(), emitter);
        }

        yaml_mapping_end_event_initialize(&event);
        exec_event(*_emitter, event);
    }
        break;

    case YamlObject::TypeArray:
        yaml_sequence_start_event_initialize(&event, 0, 0, 1, YAML_BLOCK_SEQUENCE_STYLE);
        exec_event(*_emitter, event);

        for (auto i : *yamlObject) {
            emitYaml(i, emitter);
        }

        yaml_sequence_end_event_initialize(&event);
        exec_event(*_emitter, event);

        break;

    case YamlObject::TypeInteger:
    {
        // HACK 要パフォーマンス考慮
        std::string value = std::to_string(yamlObject->integerValue());
        yaml_scalar_event_initialize(&event, 0, 0,
                                     (yaml_char_t *)value.c_str(), value.length(), 1, 0,
                                     YAML_PLAIN_SCALAR_STYLE);
        exec_event(*_emitter, event);
    }
        break;

    case YamlObject::TypeFloat:
    {
        std::string value = std::to_string(yamlObject->floatValue());
        yaml_scalar_event_initialize(&event, 0, 0,
                                     (yaml_char_t *)value.c_str(), value.length(), 1, 0,
                                     YAML_PLAIN_SCALAR_STYLE);
    }
        break;

    case YamlObject::TypeString:
    {
        auto bytes = yamlObject->stringValue().toUtf8();
        yaml_scalar_event_initialize(&event, 0, 0,
                                     (yaml_char_t *)bytes.data(), bytes.size(), 1, 1,
                                     YAML_DOUBLE_QUOTED_SCALAR_STYLE);
        exec_event(*_emitter, event);
    }
        break;

    case YamlObject::TypeBoolean:
    {
        if (yamlObject->booleanValue()) {
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

    case YamlObject::TypeNull:
        yaml_scalar_event_initialize(&event, 0, 0,
                                     (yaml_char_t *)"null", 5, 1, 0,
                                     YAML_PLAIN_SCALAR_STYLE);
        exec_event(*_emitter, event);
        break;
    }
}
