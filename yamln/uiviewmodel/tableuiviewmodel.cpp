#include "tableuiviewmodel.h"

#include "tableheaderuiviewmodel.h"
#include "tablerowuiviewmodel.h"

QString TableUIViewModel::type() const
{
    return "table";
}

TableUIViewModel::TableUIViewModel(UIViewModel *parent, YamlObjectPtr spec) :
    UIViewModel(parent)
{
    setBasicValues(spec);
    m_headers = new UIViewModelList(this);
    m_rows = new UIViewModelList(this);
    validateYamlObjectProperty("ui definition", spec, "columns", YamlObject::TypeArray);
    spec->value("columns")->forEach([this](YamlObjectPtr columnSpec) {
        m_headers->append(new TableHeaderUIViewModel(this, columnSpec));
    });
}

UIViewModelList *TableUIViewModel::headers() const
{
    return m_headers;
}

UIViewModelList *TableUIViewModel::rows() const
{
    return m_rows;
}

void TableUIViewModel::createNewRowAtLast(const QString &type)
{
    if (type.isEmpty()) {
        m_rows->append(new TableRowUIViewModel(this, m_headers));
    } else {
        // TODO
    }
}

void TableUIViewModel::setHeaders(UIViewModelList *headers)
{
    if (m_headers == headers)
        return;

    m_headers = headers;
    emit headersChanged(headers);
}

void TableUIViewModel::setRows(UIViewModelList *rows)
{
    if (m_rows == rows)
        return;

    m_rows = rows;
    emit rowsChanged(rows);
}
