#pragma once

#include <QVector>
#include <QDir>
#include <QFileInfo>
#include <QVariant>

namespace Project {

class ProjectItem
{
public:
    ProjectItem();
    ProjectItem(const QVariant &data, ProjectItem *parent);

    int childCount() const;
    ProjectItem *child(QString key);
    QVariant data() const;
    void insertChildren(QStringList items);
    ProjectItem *parent();
    bool removeChildren(QString key);
    int childNumber() const;
    void setData(const QVariant &value);

private:
    QVariant dataItem;
    ProjectItem *parentItem;
    QMap <QString, ProjectItem *> childItems;


};

}
