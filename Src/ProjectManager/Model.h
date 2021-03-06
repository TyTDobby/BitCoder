#pragma once
#include <QAbstractItemModel>
#include <QFileSystemModel>
#include <QVector>
#include <QFileSystemModel>

#include <QtAlgorithms>

#include "Project.h"
#include "Item.h"

namespace Project {

class Model : public QAbstractItemModel
{
public:
    Model(QObject *parent = 0);

public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    QModelIndex indexProject(Item *RootItem) const;

    void addProject(Project *pro);
    void refreshProject(QModelIndex index, Project *pro);
    Item *getProject(QModelIndex index);

private:
    Item *root;

};

}
