#include "tablerowuiviewmodel.h"

#include "uiviewmodellist.h"
#include "tableheaderuiviewmodel.h"
#include "tablecelluiviewmodel.h"

TableRowUIViewModel::TableRowUIViewModel(UIViewModel *parent, YamlObjectPtr spec) :
    UIViewModel(parent)
{
    m_cells = new UIViewModelList(this);
}

TableRowUIViewModel::TableRowUIViewModel(UIViewModel *parent, UIViewModelList *headers) :
    UIViewModel(parent)
{
    m_cells = new UIViewModelList(this);
    for (auto i : headers->list()) {
        auto header = qobject_cast<TableHeaderUIViewModel *>(i);
        auto cell = new TableCellUIViewModel(this, header->spec());
        m_cells->append(cell);
    }
}

UIViewModelList *TableRowUIViewModel::cells() const
{
    return m_cells;
}

void TableRowUIViewModel::setCells(UIViewModelList *cells)
{
    if (m_cells == cells)
        return;

    m_cells = cells;
    emit cellsChanged(cells);
}
