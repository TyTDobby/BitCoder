#include "Item.h"
#include <QDebug>

namespace Project {

Item::Item(Item *_parent)
    : parent(0)
    , children(QList<Item*>())
{
    //info = QFileInfo();
    setParent(_parent);
}

Item::Item(QFileInfo value, Item *_parent)
    : parent(0)
    , children(QList<Item*>())
{
    info = value;
    setParent(_parent);
}

Item::~Item()
{
    qDeleteAll(children);
    if (parent)
        parent->children.removeOne(this);
}

void Item::setRow(int row)
{
    Q_ASSERT(parent);
    if (!parent)
        return;

    parent->children.move(this->getRow(), row);
}

int Item::getRow() const
{
    return parent ? parent->children.indexOf(const_cast<Item*>(this)) : 0;
}

void Item::setParent(Item *_parent)
{
    if (parent)
        parent->children.removeOne(this);

    if (_parent)
        _parent->children.append(this);

    parent = _parent;
}

Item *Item::getParent() const
{
    return parent;
}

void Item::insertChild(int row, Item *child)
{
    Q_ASSERT(child);
    Q_ASSERT(!child->parent);

    if (child->parent)
        child->parent->removeChild(child);

    child->parent = this;
    children.insert(row, child);
}

void Item::appendChild(Item *child)
{
    Q_ASSERT(child);
    Q_ASSERT(!child->parent);

    if (child->parent)
        child->parent->removeChild(child);

    child->parent = this;
    children.append(child);
}

void Item::removeChild(Item *child)
{
    Q_ASSERT(child);
    Q_ASSERT(children.contains(child));

    children.removeOne(child);
}

Item *Item::getChild(int row) const
{
    Q_ASSERT(row < getChildCount());
    if (row < getChildCount())
        return children.at(row);
    else
        return 0;
}

int Item::getChildCount() const
{
    return children.size();
}

QList<Item*> Item::getChildren() const
{
    return children;
}

QFileInfo Item::getInfo() const
{
    return info;
}

void Item::setInfo(const QFileInfo &value)
{
    info = value;
}

}
//void Item::dump(int indent) const
//{
//    QString fill(indent, QLatin1Char(' '));
//    qDebug() << qPrintable(fill + QLatin1String("{"));
//    qDebug() << qPrintable(fill + QLatin1String(" ") + toString());
//    qDebug() << qPrintable(fill + QLatin1String(" ") + QLatin1String("this")) << this;
//    qDebug() << qPrintable(fill + QLatin1String(" ") + QLatin1String("parent")) << parent;
//    qDebug() << qPrintable(fill + QLatin1String(" ") + QLatin1String("children")) << children;

//    foreach (Item *item, children) {
//        item->dump(indent + 1);
//    }
//    qDebug() << qPrintable(fill + QLatin1String("}"));
//}


//Item::Item()
//{

//}

//Item::Item(const QVariant &data, Item *parent)
//{
//    parentItem = parent;
//    dataItem = data;
//}

//Item *Item::child(QString key)
//{
//    key.replace("/", "");
//    return childItems.value(key);
//}

//int Item::childCount() const
//{
//    return childItems.size();
//}

