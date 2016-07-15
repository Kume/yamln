#include "checkboxuiviewmodel.h"

CheckboxUIViewModel::CheckboxUIViewModel(UIViewModel *parent, const YamlObjectPtr &spec) :
    UIViewModel(parent)
{
    setBasicValues(spec);
}

QString CheckboxUIViewModel::type() const
{
    return "checkbox";
}
