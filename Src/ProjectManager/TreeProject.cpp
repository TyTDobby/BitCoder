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

    Project::Project *pro = new Project::Project("/media/tytdobby/Hard/data/123/");
    pro->setTypeProject(Project::Project_STM32);
    pro->generateProject();
    qDebug() << pro->parsing().msg;
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

TreeProject::~TreeProject()
{
    qDeleteAll(projects);
    delete view;
    delete model;
}

void TreeProject::addProject(Project::Project *pro)
{
    connect(pro, &Project::Project::changeProject,
            [=](Project::Project *pro){

        QModelIndex index = model->indexProject(pro->getRootItem());
        model->refreshProject(index, pro);
        view->setExpanded(index, true);
    });
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

void TreeProject::saveState(void)
{
//    QStringList List;

//    for (QModelIndex index : model->) {
//        if (view->isExpanded(index)) {
//            List << index.data(Qt::DisplayRole).toString();
//        }
//    }
}

void TreeProject::restoreState(void)
{
//    QStringList list;

//    for(auto &it : list) {
//        QModelIndexList Items = model->match(model->index(0, 0), Qt::DisplayRole, QVariant::fromValue(it));
//        if (!Items.isEmpty()) {
//            view->setExpanded(Items.first(), true);
//        }
//    }
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
        connect(menu, &DirFileContextMenu::refresh,
                [=](QModelIndex index){
            model->refreshProject(index, projects.at(static_cast<size_t>(index.row())));
            view->setExpanded(index, true);
        });
    }
    else {
        ProjectContextMenu *menu = new ProjectContextMenu(projects.at(static_cast<size_t>(index.row())),
                                                          this);

        menu->popup(view->viewport()->mapToGlobal(pos));
    }
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
        //QDesktopServices::openUrl(QUrl::fromLocalFile(info.absolutePath()));
    }
    else if (text == list.at(1)->text()) { // Add new

    }
    else if (text == list.at(2)->text()) { // Rename

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
        }
    }
}

ProjectContextMenu::ProjectContextMenu(Project::Project *pro,
                                       QWidget *parent)
    : QMenu(parent)
{
    list << new QAction("Build \"" + pro->getTargetName() + "\"", this)
         << new QAction("Clean", this)
         //<< new QAction("Refresh", this)
         << new QAction("Show in folder", this)
         << new QAction("Add new", this)
         << new QAction("Rename", this)
         << new QAction("Delete", this)
         << new QAction("Close \"" + pro->getTargetName() + "\"", this);
    this->pro = pro;
    addActions(list);

    connect(this, SIGNAL(triggered(QAction*)),
            SLOT(handler(QAction*)));
}

void ProjectContextMenu::handler(QAction *ac)
{
    QString text = ac->text();
    if (text == list.at(0)->text()) { //Build

    }
    else if (text == list.at(1)->text()) { // Clean

    }
    else if (text == list.at(2)->text()) { // Show in folder
        //QDesktopServices::openUrl(QUrl::fromLocalFile(pro->getRootDir()));
    }
    else if (text == list.at(3)->text()) { // Add new

    }
    else if (text == list.at(4)->text()) { // Rename

    }
    else if (text == list.at(5)->text()) { // Delete

    }
    else if (text == list.at(6)->text()) { // Close

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
