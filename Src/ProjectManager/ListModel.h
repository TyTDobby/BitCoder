#pragma once

#include <QAbstractListModel>
#include <QObject>
#include <QStringList>
#include <QIcon>

class ListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ListModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    void setList(const QStringList &list);
    void setList(const QString &value, const QString &pathIcon);
    void setIcons(const QStringList &list);

private:
    QStringList listValue, listIcon;

};

