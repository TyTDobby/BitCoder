#include "TreeProject.h"

#include <QVBoxLayout>

TreeProject::TreeProject(QWidget *parent) : QWidget(parent)
{


    treeModel = new QStandardItemModel();
    treeView = new QTreeView();

    QVBoxLayout *vBoxMain = new QVBoxLayout();

    vBoxMain->addWidget(treeView);

    treeView->setModel(treeModel);


//    treeModel->;

    vBoxMain->setMargin(0);

    setFixedWidth(250);
    setLayout(vBoxMain);

}
