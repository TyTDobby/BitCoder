#pragma once

#include <QWidget>
#include <QTreeView>
#include <QStandardItemModel>
#include <QVector>
#include "Project.h"
#include "ProjectModel.h"
//using namespace Project;

class TreeProject : public QWidget
{
    Q_OBJECT
public:
    TreeProject(QWidget *parent = 0);



private:
    QTreeView *treeView;
    ProjectModel *treeModel;
    std::vector <Project::ProjectInfo> projects;

public slots:
    void addProject(Project::ProjectInfo pro);
    void open(QModelIndex index);

};

