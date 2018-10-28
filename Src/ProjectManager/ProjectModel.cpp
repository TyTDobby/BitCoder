#include "ProjectModel.h"
#include <QtAlgorithms>

ProjectModel::ProjectModel(QObject *parent)
    : QAbstractItemModel(parent)
{

}


QModelIndex ProjectModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    if (parent.isValid()) {
        return createIndex(row,
                           column,
                           projects.at(row).getRootItem());
//                           const_cast<Project::FileSystem*>(&projects[static_cast<unsigned int>(row)]));
//                           const_cast<Project::FileSystem*>(projects.at(static_cast<unsigned int>(row)).getFileSystem()));
      }
    Project::ProjectItem* parentInfo = static_cast<Project::ProjectItem*>(parent.internalPointer());
    return createIndex(row, column, parentInfo->child(parent.data().toString()));

//    return QModelIndex();
}

QModelIndex ProjectModel::parent(const QModelIndex &child) const
{
    if (!child.isValid()) {
        return QModelIndex();
    }

    Project::ProjectItem* childInfo = static_cast<Project::ProjectItem*>(child.internalPointer());
    Project::ProjectItem* parentInfo = childInfo->parent();
    if (parentInfo != 0) {
        return createIndex(projects.size() - 1, 0, parentInfo);
    }
    else {
        return QModelIndex();
    }
}

int ProjectModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return 0;
    }
    return static_cast<int>(projects.size());
}

int ProjectModel::columnCount(const QModelIndex &parent) const
{
//    if (!parent.isValid()) {
//        return 0;
//    }
    return 1;
}

QVariant ProjectModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }
//    const Project::FileSystem* nodeInfo = static_cast<Project::FileSystem*>(index.internalPointer());
//    const QFileInfo& fileInfo = nodeInfo->fileInfo;
    switch(role){
    case Qt::DisplayRole:
        return QVariant(index.data());
    case Qt::DecorationRole:
    {
//        QDir dir(filePath(index));
//        if (dir.isRoot()) {
//            return QIcon(":icons/hdd.png");
//        }
//        if (isDir(index)) {
//            return QIcon(":icons/folder.png");
//        }
        return QIcon(":icons/file.png");
    }
    default:
        return QVariant();
    }
}

void ProjectModel::addProject(Project::Project pro)
{
    beginResetModel();
//    Project::ProjectItem &item = pro.getRootItem();
    projects.push_back(pro);
    endResetModel();
}

