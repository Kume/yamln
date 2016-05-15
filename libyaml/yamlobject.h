#ifndef YAMLOBJECT_H
#define YAMLOBJECT_H

#include <QObject>
#include <QVariant>
#include <QSharedPointer>
#include <memory>

class YamlObject;
typedef QSharedPointer<YamlObject> YamlObjectPtr;

class YamlObject : public QObject
{
    Q_OBJECT
public:
    enum Type{
        TypeObject,
        TypeArray,
        TypeInteger,
        TypeFloat,
        TypeString,
        TypeBoolean,
        TypeNull,
    };
    Q_ENUMS(Type);

    ~YamlObject();

    static YamlObject* integer(int n, QObject *parent = 0);
    static YamlObject* string(const QString &text, QObject *parent = 0);
    static YamlObject* Object(QObject *parent = 0);
    static YamlObject* Array(QObject *parent = 0);
    static YamlObject* fromFile(const QString &fileName, QObject *parent = 0);

    YamlObjectPtr operator [](const QString &key) const;
    void append(YamlObjectPtr &object);

private:
    explicit YamlObject(QObject *parent = 0);
    static YamlObject* parse(void* parser);


signals:

public slots:

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
        QList<QString> keyList;
        QHash<QString, YamlObjectPtr> map;
    };
    std::unique_ptr<VariableValue> m_variableValue;
};

#endif // YAMLOBJECT_H
