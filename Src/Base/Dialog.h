#pragma once

#include "FrameBase.h"

#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QListView>
#include <QTableView>
#include <QTreeView>
#include <QFileSystemModel>
#include <QDirModel>

class Dialog;

class Dialog : public FrameBase
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = 0);

//    QString getPath();

private:
    QPushButton *btnCancel, *btnOpen;
    QComboBox *cmbType;
    QLineEdit *editDirectory;
    QListView *view;
    QDirModel *model;
    QString path;

signals:
    void result(QString);

private slots:
    void changeDir(QModelIndex index);

public slots:
    void open();

};

