#include "tablecelluiviewmodel.h"

TableCellUIViewModel::TableCellUIViewModel(UIViewModel *parent, const YamlObjectPtr &spec) :
    UIViewModel(parent)
{
    m_content = createAtomicUIViewModel(this, spec);
}

UIViewModel *TableCellUIViewModel::content() const
{
    return m_content;
}
