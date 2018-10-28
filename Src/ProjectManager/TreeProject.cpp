#include "TreeProject.h"
#include <QVBoxLayout>
#include <QDebug>

TreeProject::TreeProject(QWidget *parent) : QWidget(parent)
{


    model = new ProjectModel();
    view = new QTreeView();

    QVBoxLayout *vBoxMain = new QVBoxLayout();

    vBoxMain->addWidget(view);

    Project::Project pro("123", "C:/Users/lymanets/123");
    pro.setTypeProject(Project::Project_STM32);
    pro.generateProject();
//    model->addProject(pro);

//    model->setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
//    model->setSorting(QDir::Type);

    view->setModel(model);
//    view->setRootIndex(model->index("C:/Users/lymanets/123"));
//    view->set
    vBoxMain->setMargin(0);

    setFixedWidth(250);
    setLayout(vBoxMain);

    connect(view, SIGNAL(doubleClicked(QModelIndex)),
            SLOT(open(QModelIndex)));

}

void TreeProject::addProject(Project::Project pro)
{
    model->addProject(pro);
}

void TreeProject::open(QModelIndex index)
{
    qDebug() << index.row();
}
