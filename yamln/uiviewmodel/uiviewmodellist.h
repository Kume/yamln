#ifndef UIVIEWMODELLIST_H
#define UIVIEWMODELLIST_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>

class UIViewModel;

class UIViewModelList : public QAbstractListModel
{
    Q_OBJECT
public:
    Q_PROPERTY(int count READ count NOTIFY countChanged)


    explicit UIViewModelList(UIViewModel *parent = 0);

    int rowCount(const QModelIndex &) const;
    int count() const;

    QVariant data(const QModelIndex &index, int role) const;

    Q_INVOKABLE void append(UIViewModel *model);
    Q_INVOKABLE void removeAt(int index);
    Q_INVOKABLE void remove(UIViewModel *model);
    Q_INVOKABLE void clear();
    Q_INVOKABLE void insert(int index, UIViewModel *model);

    const QList<UIViewModel *> &list() const;

signals:
    void countChanged();

public slots:

private:
    QList<UIViewModel *> m_list;
};

#endif // UIVIEWMODELLIST_H
