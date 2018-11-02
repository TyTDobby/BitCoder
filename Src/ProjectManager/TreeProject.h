#pragma once

#include <QWidget>
#include <QTreeView>
#include <QStandardItemModel>
#include <QVector>
#include "Project.h"
#include "Model.h"
#include "ListModel.h"
//using namespace Project;

class TreeProject : public QWidget
{
    Q_OBJECT
public:
    TreeProject(QWidget *parent = nullptr);



private:
    QTreeView *view;
    Project::Model *model;
    std::vector<Project::Project> projects;

signals:
    void openFile(QString);

public slots:
    void addProject(Project::Project pro);
    void open(QModelIndex index);
    void menu(QPoint pos);

};

