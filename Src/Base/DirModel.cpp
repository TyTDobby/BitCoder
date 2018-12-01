#include "DirModel.h"

DirModel::DirModel(QObject *parent) : QDirModel (parent)
{

}

QVariant DirModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    switch(role){
    case Qt::DisplayRole:
        return fileName(index);
    case Qt::DecorationRole:
    {
        QDir dir(filePath(index));
        if (dir.isRoot()) {
            return QIcon(":icons/hdd.png");
        }
        if (isDir(index)) {
            return QIcon(":icons/folder.png");
        }
        return QIcon(":icons/file.png");
    }
    default:
        return QVariant();
    }
}
