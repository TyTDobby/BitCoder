#include "Model.h"

namespace Project {

Model::Model(QObject *parent)
    : QAbstractItemModel(parent)
{
    root = new Item();
}

QModelIndex Model::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    Item *parentItem;

    if (!parent.isValid())
        parentItem = root;
    else
        parentItem = static_cast<Item*>(parent.internalPointer());

    Item *childItem = 0;
    if (row >= 0 && row < parentItem->getChildCount())
        childItem = parentItem->getChildren().at(row);

    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();

}

QModelIndex	Model::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    Item *childItem = static_cast<Item*>(index.internalPointer());
    Item *parentItem = childItem->getParent();

    if (parentItem == root)
        return QModelIndex();

    int row = 0;
    if (parentItem->getParent())
        row = parentItem->getRow();

    return createIndex(row, 0, parentItem);
}

int	Model::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    Item *parentItem;
    if (!parent.isValid())
        parentItem = root;
    else
        parentItem = static_cast<Item*>(parent.internalPointer());

    return parentItem->getChildren().size();
}

int Model::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }
    const Item* item = static_cast<Item*>(index.internalPointer());
    const QFileInfo& info = item->getInfo();
    switch(role){
    case Qt::DisplayRole:
        return info.fileName();
    case Qt::DecorationRole:
    {
        if (info.isDir()) {
            return QIcon(":icons/folder.png");
        }
        return QIcon(":icons/file.png");
    }
    default:
        return QVariant();
    }
}

void Model::addProject(Project pro)
{
    beginResetModel();
    root->insertChild(root->getChildCount(), pro.getRootItem());
    endResetModel();
}

void Model::refreshProject(QModelIndex index, Project pro)
{
    beginResetModel();
    int tmpRow = index.row();
    root->removeChild(static_cast<Item *>(index.internalPointer()));
    pro.generateProject();
    root->insertChild(tmpRow, pro.getRootItem());
    endResetModel();
}

}

