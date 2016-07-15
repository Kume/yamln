#ifndef TABLECELLUIVIEWMODEL_H
#define TABLECELLUIVIEWMODEL_H

#include "uiviewmodel.h"

#include <QObject>

class TableCellUIViewModel : public UIViewModel
{
    Q_OBJECT
    UIViewModel * m_content;

public:
    TableCellUIViewModel(UIViewModel *parent, const YamlObjectPtr &spec);

    Q_PROPERTY(UIViewModel *content READ content NOTIFY contentChanged)
    UIViewModel *content() const;
signals:
    void contentChanged(UIViewModel *content);
};

#endif // TABLECELLUIVIEWMODEL_H
