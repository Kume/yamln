#ifndef FORMELEMENTUIVIEWMODEL_H
#define FORMELEMENTUIVIEWMODEL_H

#include "uiviewmodel.h"

class FormUIViewModel;

class FormElementUIViewModel : public UIViewModel
{
    Q_OBJECT

public:
    Q_PROPERTY(UIViewModel* content READ content NOTIFY contentChanged)


    FormElementUIViewModel(FormUIViewModel* parent, YamlObjectPtr spec);


    // properties
    UIViewModel* content() const;

protected:
    // properties
    void setContent(UIViewModel* content);

private:
    UIViewModel *m_content;

signals:
    void contentChanged();
};

#endif // FORMELEMENTUIVIEWMODEL_H
