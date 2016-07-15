#include "formelementuiviewmodel.h"

#include "formuiviewmodel.h"

FormElementUIViewModel::FormElementUIViewModel(FormUIViewModel* parent, YamlObjectPtr spec) :
    UIViewModel(parent)
{
    m_content = createUIViewModel(this, spec);
}

UIViewModel* FormElementUIViewModel::content() const
{
    return m_content;
}
