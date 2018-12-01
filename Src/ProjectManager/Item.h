#pragma once

#include <QVector>
#include <QDir>
#include <QFileInfo>
#include <QVariant>
#include <QList>
#include <QString>

namespace Project {

//class Item
//{
//public:
//    QFileInfo info;
//    Item *parentItem;
//    QVector<Item> childItems;

//    bool operator ==(const Item& another) const
//    {
//        return this->info == another.info;
//    }

//};
//class Item
//{
//public:
//    Item();
//    Item(const QVariant &data, Item *parent);

//    int childCount() const;
//    Item *child(QString key);
//    QVariant data() const;
//    void insertChildren(QStringList items);
//    Item *parent();
//    bool removeChildren(QString key);
//    void setData(const QVariant &value);

//private:
//    QVariant dataItem;
//    Item *parentItem;
//    QMap <QString, Item *> childItems;


//};

class Item
{
public:
    explicit Item(Item *_parent = nullptr);
    explicit Item(QFileInfo value, Item *_parent = nullptr);
    ~Item();

    void setRow(int row);
    int getRow() const;

    void setParent(Item *_parent);
    Item *getParent() const;

    void insertChild(int row, Item *child);
    void appendChild(Item *child);
    void removeChild(Item *child);
    void removeChildren();

    Item *getChild(int row) const;
    int getChildCount() const;
    QList<Item*> getChildren() const;

    QFileInfo getInfo() const;
    void setInfo(const QFileInfo &value);

private:
    Item *parent;
    QList<Item*> children;
    QFileInfo info;
};

}
