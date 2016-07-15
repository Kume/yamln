#include "rootuiviewmodel.h"

RootUIViewModel::RootUIViewModel(QObject *parent, const YamlObjectPtr &spec) :
    UIViewModel(parent)
{
    m_content = createUIViewModel(this, spec);
}

UIViewModel *RootUIViewModel::content() const
{
    return m_content;
}

void RootUIViewModel::setContent(UIViewModel *content)
{
    if (m_content == content)
        return;

    m_content = content;
    emit contentChanged(content);
}

RootUIViewModel *RootUIViewModel::rootViewModel()
{
    return this;
}
