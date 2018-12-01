#pragma once

#include <QWidget>
#include <QTreeView>
#include <QStandardItemModel>
#include <QVector>
#include "Project.h"
#include "Model.h"
#include "ListModel.h"
#include <QMenu>
#include <QAction>
#include <QItemDelegate>

class TreeProject;
class DirFileContextMenu;
class ProjectContextMenu;
class LineDelegate;

class TreeProject : public QWidget
{
    Q_OBJECT
public:
    TreeProject(QWidget *parent = 0);
    ~TreeProject();

private:
    QTreeView *view;
    Project::Model *model;
    std::vector<Project::Project *> projects;
    QList<QAction *> dirActions, fileActions, projectActions;

    QModelIndex getRootIndex(QModelIndex index);
    void restoreState();
    void saveState();

signals:
    void openFile(QString);

public slots:
    void addProject(Project::Project *pro);
    void open(QModelIndex index);
    void contextMenu(QPoint pos);
//    void refresh(QModelIndex index);

};

class DirFileContextMenu : public QMenu
{
    Q_OBJECT
public:
    DirFileContextMenu(QFileInfo info,
                       QModelIndex index,
                       QWidget *parent);

signals:
    void refresh(QModelIndex);

private:
    QList<QAction *> list;
    QFileInfo info;
    Project::Project *pro;
    QModelIndex index;

public slots:
    void handler(QAction *ac);

};

class ProjectContextMenu : public QMenu
{
    Q_OBJECT
public:
    ProjectContextMenu(Project::Project *pro,
                       QWidget *parent);

signals:
    void refresh(QModelIndex);

private:
    QList<QAction *> list;
    Project::Project *pro;
    QModelIndex index;

public slots:
    void handler(QAction *ac);

};

class LineDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    LineDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option, const QModelIndex &index) const;
};
