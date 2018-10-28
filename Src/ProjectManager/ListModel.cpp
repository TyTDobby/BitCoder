#include "ListModel.h"

ListModel::ListModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

int ListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return listValue.count();
}

QVariant ListModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }
    switch(role){
    case Qt::DisplayRole:
        return listValue.at(index.row());
    case Qt::DecorationRole:
        if(listIcon.length() > 0) {
            return QImage(listIcon.at(index.row()));
        }
        break;
    }
    return QVariant();
}

bool ListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role == Qt::EditRole) {
        listValue.replace(index.row(), value.toString());
    }
    return true;

}

Qt::ItemFlags ListModel::flags(const QModelIndex &index) const
{
    if(!index.isValid()) {
        return Qt::NoItemFlags;
    }
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void ListModel::setList(const QStringList &list)
{
    beginResetModel();
    listValue = list;
    endResetModel();
}

void ListModel::setList(const QString &value, const QString &pathIcon)
{
    beginResetModel();
    listValue << value;
    listIcon << pathIcon;
    endResetModel();
}

void ListModel::setIcons(const QStringList &list)
{
    beginResetModel();
    listIcon = list;
    endResetModel();
}
