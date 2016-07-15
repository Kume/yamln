#ifndef TABLEUIVIEWMODEL_H
#define TABLEUIVIEWMODEL_H

#include "uiviewmodel.h"
#include "uiviewmodellist.h"

class TableUIViewModel : public UIViewModel
{
    Q_OBJECT

    UIViewModelList *m_headers;

    UIViewModelList *m_rows;

public:
    Q_PROPERTY(UIViewModelList* headers READ headers WRITE setHeaders NOTIFY headersChanged)
    Q_PROPERTY(UIViewModelList* rows READ rows WRITE setRows NOTIFY rowsChanged)

    virtual QString type() const;

    TableUIViewModel(UIViewModel *parent, YamlObjectPtr spec);
    UIViewModelList *headers() const;
    UIViewModelList *rows() const;

    Q_INVOKABLE void createNewRowAtLast(const QString &type);

public slots:
    void setHeaders(UIViewModelList *headers);
    void setRows(UIViewModelList *rows);

signals:
    void headersChanged(UIViewModelList *headers);
    void rowsChanged(UIViewModelList *rows);
};

#endif // TABLEUIVIEWMODEL_H
