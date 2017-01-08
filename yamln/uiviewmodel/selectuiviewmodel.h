#ifndef SELECTUIVIEWMODEL_H
#define SELECTUIVIEWMODEL_H

#include "uiviewmodel.h"

#include <QObject>

class SelectUIViewModel : public UIViewModel
{
    Q_OBJECT
public:
    explicit SelectUIViewModel(QObject *parent = 0);

signals:

public slots:
};

#endif // SELECTUIVIEWMODEL_H
