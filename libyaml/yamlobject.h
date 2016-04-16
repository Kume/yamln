#ifndef YAMLOBJECT_H
#define YAMLOBJECT_H

#include <QObject>
#include <memory>

class YamlObjectPrivate;

class YamlObject : public QObject
{
    Q_OBJECT
public:
    explicit YamlObject(QObject *parent = 0);

    static YamlObject* fromFile(const QString &fileName);

private:
    static YamlObject* parse(void* parser);

signals:

public slots:

private:
};

#endif // YAMLOBJECT_H
