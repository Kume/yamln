#ifndef FORMUIVIEWMODEL_H
#define FORMUIVIEWMODEL_H

#include "uiviewmodel.h"

#include <QList>

class UIViewModelList;

class FormUIViewModel : public UIViewModel
{
    Q_OBJECT

public:
    Q_PROPERTY(UIViewModelList* elements READ elements NOTIFY elementsChanged)


    FormUIViewModel(UIViewModel *parent, const YamlObjectPtr &spec);

    virtual QString type() const;

    void append(YamlObjectPtr spec);
    UIViewModelList *elements() const;

public slots:

signals:
    void elementsChanged(UIViewModelList* elements);

private:
    UIViewModelList *m_elements;
};

#endif // FORMUIVIEWMODEL_H
