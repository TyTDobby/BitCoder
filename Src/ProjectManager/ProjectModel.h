#ifndef PROJECTMODEL_H
#define PROJECTMODEL_H

#include <QAbstractItemModel>
#include <QFileSystemModel>
#include <QVector>
#include <QDirModel>

#include "Project.h"
#include "ProjectItem.h"

class ProjectModel : public QAbstractItemModel
{
public:
    ProjectModel(QObject *parent = NULL);

public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    void addProject(Project::Project pro);

private:
    std::vector<Project::Project> projects;
};

#endif // PROJECTMODEL_H
