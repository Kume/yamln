#include "yamlobjectparser.h"

YamlObjectParser::YamlObjectParser()
{

}

ActiveYaml::YamlObjectPtr ActiveYaml::YamlObjectParser::fromFile(const QString &fileName)
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

ActiveYaml::YamlObjectPtr ActiveYaml::YamlObjectParser::fromFile(QFile &file)
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
