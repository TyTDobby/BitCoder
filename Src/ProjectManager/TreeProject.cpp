#include "TreeProject.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>
#include <QThread>

#include "Dialog.h"

TreeProject::TreeProject(QWidget *parent) : QWidget(parent)
{
    model = new Project::Model();
    view = new QTreeView();

    QVBoxLayout *vBoxMain = new QVBoxLayout();
    LineDelegate *delegate = new LineDelegate();
    vBoxMain->addWidget(view);

    Project::Project pro("123", QDir::homePath() + "/123");
    pro.setTypeProject(Project::Project_STM32);
    pro.generateProject();

    addProject(pro);

    view->setModel(model);
    view->setContextMenuPolicy(Qt::CustomContextMenu);
    view->setItemDelegate(delegate);
    vBoxMain->setMargin(0);

    setFixedWidth(250);
    setLayout(vBoxMain);

    connect(view, SIGNAL(doubleClicked(QModelIndex)),
            SLOT(open(QModelIndex)));
    connect(view, SIGNAL(customContextMenuRequested(QPoint)),
            SLOT(contextMenu(QPoint)));

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
        if (!item->getInfo().isDir()) {
            QFile file(item->getInfo().absoluteFilePath());
            file.open(QIODevice::ReadWrite);
            emit openFile(file.readAll());
        }
    }
}

QModelIndex TreeProject::getRootIndex(QModelIndex index)
{
    if(model->parent(index).data().isValid()) {
       return getRootIndex(model->parent(index));
    }
    return index;
}

void TreeProject::contextMenu(QPoint pos)
{

    QModelIndex index = view->indexAt(pos);
    Project::Item *item = static_cast<Project::Item *>(index.internalPointer());
    QModelIndex root = getRootIndex(index);

    if (model->parent(index).data().isValid()) {
        DirFileContextMenu *menu = new DirFileContextMenu(item->getInfo().absoluteFilePath(),
                                                          root,
                                                          this);
        menu->popup(view->viewport()->mapToGlobal(pos));
        connect(menu, SIGNAL(refresh(QModelIndex)),
                SLOT(refresh(QModelIndex)));
    }
    else {
        ProjectContextMenu *menu = new ProjectContextMenu(index,
                                                          this);
//        Project::Project pro = projects.at(index.row());
//        pro.generateProject();
        model->refreshProject(index, projects.at(index.row()));
        //projects.erase(projects.begin() + index.row());
//        projects.push_back(pro);
        menu->popup(view->viewport()->mapToGlobal(pos));
    }
}

void TreeProject::refresh(QModelIndex index)
{
    Project::Project pro = projects.at(index.row());
    projects.erase(projects.begin() + index.row());
    pro.generateProject();
    projects.push_back(pro);
}

DirFileContextMenu::DirFileContextMenu(QFileInfo info,
                                       QModelIndex index,
                                       QWidget *parent)
    : QMenu(parent)
{
    list << new QAction("Show in folder", this)
         << new QAction("Add new", this)
         << new QAction("Rename", this)
         << new QAction("Delete", this);
    this->info = info;
    this->index = index;
    addActions(list);

    connect(this, SIGNAL(triggered(QAction*)),
            SLOT(handler(QAction*)));
}

void DirFileContextMenu::handler(QAction *ac)
{
    QString text = ac->text();
    if (text == list.at(0)->text()) { // Show in folder
        QDesktopServices::openUrl(QUrl::fromLocalFile(info.absolutePath()));
    }
    else if (text == list.at(1)->text()) { // Add new

    }
    else if (text == list.at(2)->text()) { // Rename
//        QDe
    }
    else if (text == list.at(3)->text()) { // Delete
        if (info.isDir()) {
            Project::Project::removeDir(info.absoluteFilePath());
        }
        else {
            QFile().remove(info.absoluteFilePath());
        }
        if (!QDir(info.absoluteFilePath()).exists()) {
            emit refresh(index);
            //QThread::msleep(1000);
           // pro->generateProject();
        }
    }
}

ProjectContextMenu::ProjectContextMenu(QModelIndex index,
                                       QWidget *parent)
    : QMenu(parent)
{
    list << new QAction("Build \"" + index.data().toString() + "\"", this)
         << new QAction("Clean", this)
         << new QAction("Refresh", this)
         << new QAction("Show in folder", this)
         << new QAction("Show in folder", this)
         << new QAction("Add new", this)
         << new QAction("Rename", this)
         << new QAction("Delete", this)
         << new QAction("Close \"" + index.data().toString() + "\"", this);
    this->index = index;
    addActions(list);

    connect(this, SIGNAL(triggered(QAction*)),
            SLOT(handler(QAction*)));
}

void ProjectContextMenu::handler(QAction *ac)
{
    QString text = ac->text();
    if (text == list.at(0)->text()) { //Build
       // QDesktopServices::openUrl(QUrl::fromLocalFile(info.absolutePath()));
    }
    else if (text == list.at(1)->text()) { // Clean

    }
    else if (text == list.at(2)->text()) { // Refresh
//        Project::Project *tmp = new Project::Project(QFileInfo(pro->getRootDir()).fileName(),
//                                                     pro->getRootDir());
//        tmp->setOutputDir(pro->getRootDir());
//        tmp->setTypeProject(pro->getTypeProject());
//        tmp
        //pro->generateProject();
        //emit refresh(index);
    }
    else if (text == list.at(2)->text()) { // Rename
//        QDe
    }
    else if (text == list.at(3)->text()) { // Delete
//        qDebug() << info.absoluteFilePath();
//        if (!info.isDir()) {
//            QDir dir(info.absoluteFilePath());
//            dir.remove(info.absoluteFilePath());
//        }
//        else {
//            QFile file(info.absoluteFilePath());
//            file.remove();
//        }
//        emit refresh();
    }
}

LineDelegate::LineDelegate(QObject *parent)
{

}

QWidget *LineDelegate::createEditor(QWidget *parent,
                                    const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    return editor;
}

void LineDelegate::setEditorData(QWidget *editor, const
                                 QModelIndex &index) const
{
    QLineEdit *line = static_cast<QLineEdit*>(editor);
    line->setText(index.model()->data(index, Qt::DisplayRole).toString());
}

void LineDelegate::setModelData(QWidget *editor,
                                QAbstractItemModel *model,
                                const QModelIndex &index) const
{
    QLineEdit *line = static_cast<QLineEdit*>(editor);
//    spinBox->interpretText();

    model->setData(index, line->text(), Qt::EditRole);
}

void LineDelegate::updateEditorGeometry(QWidget *editor,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{
     editor->setGeometry(option.rect);
}
