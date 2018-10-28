#pragma once

#include <QWidget>
#include <QTreeView>
#include <QStandardItemModel>
#include <QVector>
#include "Project.h"
#include "ProjectModel.h"
#include "DirModel.h"
//using namespace Project;

class TreeProject : public QWidget
{
    Q_OBJECT
public:
    TreeProject(QWidget *parent = NULL);



private:
    QTreeView *view;
    ProjectModel *model;

public slots:
    void addProject(Project::Project pro);
    void open(QModelIndex index);

};

