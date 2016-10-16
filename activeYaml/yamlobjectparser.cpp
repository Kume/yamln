#include "yamlobjectparser.h"

#include <yaml.h>
#include <QDebug>

#include "activeyamlutil.h"
#include "activeyamlexception.h"

using namespace ActiveYaml;

bool YamlObjectParser::isDebugOutputEnabled = false;

YamlObjectParser::YamlObjectParser()
{

}

ActiveYaml::YamlObjectPtr YamlObjectParser::fromFile(const QString &fileName)
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

ActiveYaml::YamlObjectPtr YamlObjectParser::fromFile(QFile &file)
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

YamlObjectPtr YamlObjectParser::parse(void *parser_)
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
            if (ActiveYamlUtil::isIntegerString(value) && style != YAML_PLAIN_SCALAR_STYLE) {
                yamlValue = YamlObjectPtr(YamlObject::integer(value.toInt()));
            } else if (ActiveYamlUtil::isFloatString(value) && style != YAML_PLAIN_SCALAR_STYLE) {
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
