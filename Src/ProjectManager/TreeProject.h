#pragma once

#include <QWidget>
#include <QTreeView>
#include <QStandardItemModel>

class TreeProject : public QWidget
{
    Q_OBJECT
public:
    TreeProject(QWidget *parent = 0);



private:
    QTreeView *treeView;
    QStandardItemModel *treeModel;

};

