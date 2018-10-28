#pragma once


#include <QAbstractListModel>
#include <QObject>
#include <QStringList>
#include <QIcon>
#include <QDir>
#include <QDirModel>
#include <QModelIndex>

class DirModel : public QDirModel
{

public:
    explicit DirModel(QObject *parent = NULL);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};
