#include "ProjectItem.h"

namespace Project {

ProjectItem::ProjectItem()
{

}

ProjectItem::ProjectItem(const QVariant &data, ProjectItem *parent)
{
    parentItem = parent;
    dataItem = data;
}

ProjectItem *ProjectItem::child(QString key)
{
    return childItems.value(key);
}

int ProjectItem::childCount() const
{
    return childItems.count();
}

QVariant ProjectItem::data() const
{
    return dataItem;
}

void ProjectItem::insertChildren(QStringList items)
{
    for (auto &it : items) {
        childItems.insert(it, new ProjectItem(it, this));
    }
}

ProjectItem *ProjectItem::parent()
{
    return parentItem;
}

bool ProjectItem::removeChildren(QString key)
{
//    if (children.find(key)){
//        return false;
//    }
    childItems.remove(key);

    return true;
}

void ProjectItem::setData(const QVariant &value)
{
    dataItem = value;
}

}
