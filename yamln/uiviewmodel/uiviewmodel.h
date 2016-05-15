#ifndef UIVIEWMODEL_H
#define UIVIEWMODEL_H

#include <QObject>
#include "yamlobject.h"

class UIViewModel : public QObject
{
    Q_OBJECT

    enum class Type : int {
        Root,
        Tab,
        SelectBox,
        Form,
        Table,
        Text,
        Select,
    };

public:

protected:
    explicit UIViewModel(QObject *parent = 0);
    static UIViewModel* createUIViewModel(YamlObject* source, UIViewModel* parent);

signals:

public slots:
};

#endif // UIVIEWMODEL_H
