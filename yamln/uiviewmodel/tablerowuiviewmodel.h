#ifndef TABLEROWUIVIEWMODEL_H
#define TABLEROWUIVIEWMODEL_H

#include "uiviewmodel.h"

class UIViewModelList;

class TableRowUIViewModel : public UIViewModel
{
    Q_OBJECT
    UIViewModelList* m_cells;

public:
    Q_PROPERTY(UIViewModelList* cells READ cells NOTIFY cellsChanged)

    TableRowUIViewModel(UIViewModel *parent, YamlObjectPtr spec);
    TableRowUIViewModel(UIViewModel *parent, UIViewModelList* headers);

    UIViewModelList* cells() const;

private:
    void setCells(UIViewModelList* cells);

public slots:

signals:
    void cellsChanged(UIViewModelList* cells);
};

#endif // TABLEROWUIVIEWMODEL_H
