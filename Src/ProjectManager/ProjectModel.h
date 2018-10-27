#ifndef PROJECTMODEL_H
#define PROJECTMODEL_H

#include <QAbstractItemModel>

class ProjectModel : public QAbstractItemModel
{
public:
    ProjectModel(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // PROJECTMODEL_H
