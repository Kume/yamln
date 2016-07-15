#include "formuiviewmodel.h"

#include <yamlobject.h>
#include "uiviewmodellist.h"
#include "formelementuiviewmodel.h"

FormUIViewModel::FormUIViewModel(UIViewModel *parent, const YamlObjectPtr &spec) :
    UIViewModel(parent)
{
    m_elements = new UIViewModelList(this);

    validateYamlObjectProperty("ui definition", spec, "contents", YamlObject::TypeArray);
    spec->value("contents")->forEach([this](YamlObjectPtr contentSpec) {
        append(contentSpec);
    });
}

QString FormUIViewModel::type() const
{
    return "form";
}

UIViewModelList *FormUIViewModel::elements() const
{
    return m_elements;
}

void FormUIViewModel::append(YamlObjectPtr spec)
{
    m_elements->append(new FormElementUIViewModel(this, spec));
}
