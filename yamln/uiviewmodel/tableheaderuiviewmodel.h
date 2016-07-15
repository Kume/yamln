#ifndef TABLEHEADERUIVIEWMODEL_H
#define TABLEHEADERUIVIEWMODEL_H

#include "uiviewmodel.h"


class TableHeaderUIViewModel : public UIViewModel
{
    Q_OBJECT
public:


    TableHeaderUIViewModel(UIViewModel *parent, const YamlObjectPtr &spec);

    const YamlObjectPtr &spec() const;

private:
    YamlObjectPtr m_spec;
};

#endif // TABLEHEADERUIVIEWMODEL_H
