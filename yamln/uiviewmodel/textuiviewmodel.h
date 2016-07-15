#ifndef TEXTUIVIEWMODEL_H
#define TEXTUIVIEWMODEL_H

#include "uiviewmodel.h"
#include <yamlobject.h>

class TextUIViewModel : public UIViewModel
{
    Q_OBJECT
    QString m_value;

public:
    Q_PROPERTY(QString value READ value NOTIFY valueChanged)

    virtual QString type() const;

TextUIViewModel(UIViewModel *parent, YamlObjectPtr spec);
QString value() const;
public slots:
signals:
void valueChanged(QString value);
};

#endif // TEXTUIVIEWMODEL_H
