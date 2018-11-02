#include "TreeProject.h"
#include <QVBoxLayout>
#include <QDebug>
//#include <QAbstractItemModelTester>

TreeProject::TreeProject(QWidget *parent) : QWidget(parent)
{


    model = new Project::Model();
    view = new QTreeView();

    QVBoxLayout *vBoxMain = new QVBoxLayout();

    vBoxMain->addWidget(view);

    Project::Project pro("123", QDir::homePath() + "/123");
    pro.setTypeProject(Project::Project_STM32);
    pro.generateProject();

    addProject(pro);


    view->setModel(model);
    view->setContextMenuPolicy(Qt::CustomContextMenu);

    vBoxMain->setMargin(0);

    setFixedWidth(250);
    setLayout(vBoxMain);

    connect(view, SIGNAL(doubleClicked(QModelIndex)),
            SLOT(open(QModelIndex)));
    connect(view, SIGNAL(customContextMenuRequested(QPoint)),
            SLOT(menu(QPoint)));

}

void TreeProject::addProject(Project::Project pro)
{
    projects.push_back(pro);
    model->addProject(pro);
}

void TreeProject::open(QModelIndex index)
{
    Project::Item *item = static_cast<Project::Item *>(index.internalPointer());

    if (model->parent(index).data().isValid()) {
        if (item->getInfo().isDir()) {
            qDebug() << "Folder";
        }
        else {
            qDebug() << "File";
            QFile file(item->getInfo().absoluteFilePath());
            file.open(QIODevice::ReadWrite);
            emit openFile(file.readAll());
        }
    }
    else {
        qDebug() << projects.size();
        qDebug() << index.row();
        //projects.at(index.row()).generateProject();
        qDebug() << "Project";
    }

}

void TreeProject::menu(QPoint pos)
{
    QModelIndex index = view->indexAt(pos);
    Project::Item *item = static_cast<Project::Item *>(index.internalPointer());

    //if ()
    if (model->parent(index).data().isValid()) {
        if (item->getInfo().isDir()) {
            qDebug() << "Folder";
        }
        else {
            qDebug() << "File";
            QFile file(item->getInfo().absoluteFilePath());
            file.open(QIODevice::ReadWrite);
            emit openFile(file.readAll());
        }
    }
    else {
        qDebug() << projects.size();
        qDebug() << index.row();
        Project::Project pro = projects.at(index.row());
        projects.erase(projects.begin() + index.row());
        pro.generateProject();
        addProject(pro);
        qDebug() << "Project";
    }
}
