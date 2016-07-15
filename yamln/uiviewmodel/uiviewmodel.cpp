#include "uiviewmodel.h"

#include "textuiviewmodel.h"
#include "formuiviewmodel.h"
#include "tableuiviewmodel.h"
#include "checkboxuiviewmodel.h"

#include "exceptions/yamlobjectexception.h"

UIViewModel::UIViewModel(UIViewModel *parent) : QObject(parent)
{

}

UIViewModel* UIViewModel::createUIViewModel(UIViewModel *parent, const YamlObjectPtr &spec)
{
    auto atomicUiViewModel = createAtomicUIViewModel(parent, spec);
    if (atomicUiViewModel) {
        return atomicUiViewModel;
    }

    validateYamlObjectProperty("ui definition", spec, "type", YamlObject::TypeString);
    QString type = spec->value("type")->stringValue();

    if (type == "form") {
        return new FormUIViewModel(parent, spec);
    }

    if (type == "table") {
        return new TableUIViewModel(parent, spec);
    }

    return 0;
}

UIViewModel* UIViewModel::createAtomicUIViewModel(UIViewModel *parent, const YamlObjectPtr &spec)
{
    validateYamlObjectProperty("ui definition", spec, "type", YamlObject::TypeString);
    QString type = spec->value("type")->stringValue();

    if (type == "text") {
        TextUIViewModel *viewModel = new TextUIViewModel(parent, spec);

        return viewModel;
    }

    if (type == "datetime") {

    }

    if (type == "integer") {

    }

    if (type == "checkbox") {
        return new CheckboxUIViewModel(parent, spec);
    }

    // 対応してないタイプは親側で例外を投げる
    return 0;
}

QString UIViewModel::label() const
{
    return m_label;
}

void UIViewModel::setLabel(QString label)
{
    m_label = label;
    emit labelChanged();
}

bool UIViewModel::isVisible() const
{
    return m_isVisible;
}

void UIViewModel::setIsVisible(bool isVisible)
{
    m_isVisible = isVisible;
    emit isVisibleChanged();
}

YamlPath UIViewModel::path() const
{
    return m_path;
}

QString UIViewModel::type() const
{
    return "";
}

UIViewModel *UIViewModel::parentViewModel() const
{
    return qobject_cast<UIViewModel *>(parent());
}

RootUIViewModel *UIViewModel::rootViewModel()
{
    auto parent = parentViewModel();
    if (parent) {
        return parent->rootViewModel();
    } else {
        return nullptr;
    }
}

UIViewModel::UIViewModel(QObject *parent) :
    QObject(parent)
{

}

void UIViewModel::setPath(const YamlPath &path)
{
    m_path = path;
    emit pathChanged();
}

void UIViewModel::setBasicValues(const YamlObjectPtr &spec)
{
    validateYamlObjectProperty("ui definition", spec, "label", YamlObject::TypeString);
    setLabel(spec->value("label")->stringValue());

    validateYamlObjectProperty(
                "ui definition", spec, "path",
                QVector<YamlObject::Type> {YamlObject::TypeString, YamlObject::TypeArray});
    YamlObjectPtr path = spec->value("path");
    switch (path->type()) {
    case YamlObject::TypeString:
        setPath(YamlPath::parse(path->stringValue()));
        break;

    case YamlObject::TypeArray:
        // TODO
        break;
    }
}


// utilities
void UIViewModel::validateYamlObjectType(const QString &objectName, const YamlObjectPtr &object, YamlObject::Type expectedType)
{
    if (object->type() != expectedType) {
        throw YamlObjectException(objectName + " must be " + YamlObject::typeToName(object->type()) + " type.", object);
    }
}

void UIViewModel::validateYamlObjectPropertyExistence(const QString &objectName, const YamlObjectPtr &object, const QString &propertyName)
{
    if (object->type() != YamlObject::TypeObject) {
        throw YamlObjectException(objectName + " must be Object type.", object);
    }

    if (!object->contains(propertyName)) {
        throw YamlObjectException(objectName + " must have " + propertyName + " property.", object);
    }
}

void UIViewModel::validateYamlObjectProperty(const QString &objectName, const YamlObjectPtr &object, const QString &propertyName, YamlObject::Type expectedType)
{
    validateYamlObjectPropertyExistence(objectName, object, propertyName);
    validateYamlObjectType(propertyName, object->value(propertyName), expectedType);
}

void UIViewModel::validateYamlObjectProperty(const QString &objectName, const YamlObjectPtr &object, const QString &propertyName, QVector<YamlObject::Type> expectedTypes)
{
    validateYamlObjectPropertyExistence(objectName, object, propertyName);

    YamlObjectPtr property = object->value(propertyName);

    bool isMatch = false;
    for (auto i : expectedTypes) {
        if (i == property->type()) {
            isMatch = true;
            break;
        }
    }

    if (!isMatch) {
        QStringList typeNames;
        for (auto i : expectedTypes) {
            typeNames.append(YamlObject::typeToName(i));
        }
        throw YamlObjectException(propertyName + " property must be " + typeNames.join("/") + ".", object->value("type"));
        // TODO message
    }
}

void UIViewModel::setType(QString type)
{
    if (m_type == type)
        return;

    m_type = type;
    emit typeChanged(type);
}
