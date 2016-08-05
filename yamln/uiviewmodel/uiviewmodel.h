#ifndef UIVIEWMODEL_H
#define UIVIEWMODEL_H

#include <QObject>
#include <QVector>
#include "yamlobject.h"
#include "yamlpath.h"

using namespace ActiveYaml;

class RootUIViewModel;

class UIViewModel : public QObject
{
    Q_OBJECT

public:

    enum class Type : int {
        Root,
        Tab,
        SelectBox,
        Form,
        Table,
        Text,
        Select,
    };
    Q_ENUM(Type)

    explicit UIViewModel(UIViewModel *parent = 0);
    virtual ~UIViewModel();

    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
    Q_PROPERTY(bool isVisible READ isVisible NOTIFY isVisibleChanged)
    Q_PROPERTY(YamlPath path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QString type READ type NOTIFY typeChanged)

    QString label() const;
    void setLabel(QString label);
    bool isVisible() const;
    YamlPath path() const;
    virtual QString type() const;
    UIViewModel *parentViewModel() const;
    virtual RootUIViewModel *rootViewModel();

protected:
    explicit UIViewModel(QObject *parent);

    static UIViewModel* createUIViewModel(UIViewModel *parent, const YamlObjectPtr &source);
    static UIViewModel* createAtomicUIViewModel(UIViewModel *parent, const YamlObjectPtr &source);

    void setIsVisible(bool isVisible);
    void setPath(const YamlPath& path);
    void setBasicValues(const YamlObjectPtr &spec);

    // utilities
    void mapProperty(const YamlObjectPtr &source,
                     const char *propertyName,
                     YamlObject::Type type,
                     bool required,
                     const YamlObjectPtr &defaultValue);

    static void validateYamlObjectType(const QString& objectName,
                                       const YamlObjectPtr& object,
                                       YamlObject::Type expectedType);
    static void validateYamlObjectPropertyExistence(const QString& objectName,
                                                    const YamlObjectPtr& object,
                                                    const QString& propertyName);
    static void validateYamlObjectProperty(const QString& objectName,
                                           const YamlObjectPtr& object,
                                           const QString& propertyName,
                                           YamlObject::Type expectedType);
    static void validateYamlObjectProperty(const QString& objectName,
                                           const YamlObjectPtr& object,
                                           const QString& propertyName,
                                           QVector<YamlObject::Type> expectedTypes);

private:
    void setType(QString type);

signals:
    void labelChanged();
    void isVisibleChanged();
    void pathChanged();

    void typeChanged(QString type);

public slots:

private:
    QString m_label;
    YamlPath m_path;
    bool m_isVisible;
    QString m_type;
};

#endif // UIVIEWMODEL_H
