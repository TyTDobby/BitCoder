#pragma once

#include "FrameBase.h"
#include "DirModel.h"

#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QListView>
#include <QTableView>
#include <QTreeView>
#include <QFileSystemModel>

class Dialog;

class Dialog : public FrameBase
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = NULL);

//    QString getPath();

private:
    QPushButton *btnCancel, *btnOpen;
    QComboBox *cmbType;
    QLineEdit *editDirectory;
    QListView *view, *viewHard;
    DirModel *model, *modelHard;
    QString path;

signals:
    void result(QString);

private slots:
    void changeHard(QModelIndex index);
    void changeDir(QModelIndex index);
    void changeText(QString text);

public slots:
    void open();

};

