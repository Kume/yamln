#include "yamlobject.h"

#include <exception>
#include <QDebug>
#include <yaml.h>

YamlObject::YamlObject(QObject *parent) : QObject(parent)
{

}

YamlObject* YamlObject::fromFile(const QString &fileName)
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
        parse(&parser);
    } catch (std::exception &e) {

    }

    yaml_parser_delete(&parser);
    fclose(file);
}

YamlObject* YamlObject::parse(void *parser_)
{
    yaml_parser_t* parser = (yaml_parser_t*)parser_;
    bool is_done = false;
    yaml_event_t event;
    YamlObject* currentObject = 0;

    while (!is_done) {
        if (!yaml_parser_parse(parser, &event)) {
            delete currentObject;
            throw new std::exception("parse error");
        }

        switch (event.type) {
        case YAML_NO_EVENT:
            qDebug() << "YAML_NO_EVENT";
            break;

        case YAML_STREAM_START_EVENT:
            qDebug() << "YAML_STREAM_START_EVENT";
            break;

        case YAML_STREAM_END_EVENT:
            qDebug() << "YAML_STREAM_END_EVENT";
            break;

        case YAML_DOCUMENT_START_EVENT:
            qDebug() << "YAML_DOCUMENT_START_EVENT";
            break;
        case YAML_DOCUMENT_END_EVENT:
            qDebug() << "YAML_DOCUMENT_END_EVENT";
            is_done = true;
            break;

        case YAML_ALIAS_EVENT:
            qDebug() << "YAML_ALIAS_EVENT";
            break;

        case YAML_SCALAR_EVENT:
            qDebug() << "YAML_SCALAR_EVENT " << QString::fromUtf8((char *)event.data.scalar.value);
            qDebug() << event.start_mark.line << " " << event.end_mark.line;
            break;

        case YAML_SEQUENCE_START_EVENT:
            qDebug() << "YAML_SEQUENCE_START_EVENT";
            break;
        case YAML_SEQUENCE_END_EVENT:
            qDebug() << "YAML_SEQUENCE_END_EVENT";
            break;
        case YAML_MAPPING_START_EVENT:
            qDebug() << "YAML_MAPPING_START_EVENT";
            break;
        case YAML_MAPPING_END_EVENT:
            qDebug() << "YAML_MAPPING_END_EVENT";
            break;
        }
    }
}
