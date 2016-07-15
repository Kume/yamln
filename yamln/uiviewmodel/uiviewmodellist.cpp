#include "uiviewmodellist.h"

#include "uiviewmodel.h"

UIViewModelList::UIViewModelList(UIViewModel *parent) :
    QAbstractListModel(parent)
{

}

int UIViewModelList::rowCount(const QModelIndex &) const
{
    return m_list.size();
}

int UIViewModelList::count() const
{
    return m_list.size();
}

QVariant UIViewModelList::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role);
    return QVariant::fromValue(m_list.at(index.row()));
}

void UIViewModelList::append(UIViewModel *model)
{
    beginInsertRows(QModelIndex(), m_list.size(), m_list.size());
    m_list.append(model);
    endInsertRows();
    emit countChanged();
}

void UIViewModelList::removeAt(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    auto element = m_list.at(index);
    element->deleteLater();
    m_list.removeAt(index);
    endRemoveRows();
    emit countChanged();
}

void UIViewModelList::remove(UIViewModel *model)
{
    removeAt(m_list.indexOf(model));
}

void UIViewModelList::clear()
{
    beginRemoveRows(QModelIndex(), 0, m_list.size());
    foreach (auto element, m_list) {
        element->deleteLater();
    }
    m_list.clear();
    endRemoveRows();
    emit countChanged();
}

void UIViewModelList::insert(int index, UIViewModel *model)
{
    beginInsertRows(QModelIndex(), index, index);
    m_list.insert(index, model);
    endInsertRows();
    emit countChanged();
}

const QList<UIViewModel *> &UIViewModelList::list() const
{
    return m_list;
}
