#include "TreeProject.h"
#include <QVBoxLayout>
#include <QDebug>

TreeProject::TreeProject(QWidget *parent) : QWidget(parent)
{


    treeModel = new ProjectModel();
    treeView = new QTreeView();

    QVBoxLayout *vBoxMain = new QVBoxLayout();

    vBoxMain->addWidget(treeView);

    treeView->setModel(treeModel);

    vBoxMain->setMargin(0);

    setFixedWidth(250);
    setLayout(vBoxMain);

    connect(treeView, SIGNAL(doubleClicked(QModelIndex)),
            SLOT(open(QModelIndex)));

}

void TreeProject::addProject(Project::ProjectInfo pro)
{
    treeView->setRootIndex(treeModel->index(pro.getRootDir()));
    projects.push_back(pro);
}

void TreeProject::open(QModelIndex index)
{
    qDebug() << index.row();
}
