#ifndef CHECKBOXUIVIEWMODEL_H
#define CHECKBOXUIVIEWMODEL_H

#include "uiviewmodel.h"



class CheckboxUIViewModel : public UIViewModel
{
    Q_OBJECT

public:
    CheckboxUIViewModel(UIViewModel *parent, const YamlObjectPtr &spec);



    // UIViewModel interface
public:
    virtual QString type() const override;
};

#endif // CHECKBOXUIVIEWMODEL_H
