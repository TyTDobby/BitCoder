#include "Dialog.h"

#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QComboBox>
#include <QFileIconProvider>
#include <QDebug>
#include <QApplication>

Dialog::Dialog(QWidget *parent) : FrameBase(parent)
{
    setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | windowFlags());
    setWindowButtons(WindowButton::Closed);
    setTitleText("Browse");

    setFixedSize(680, 480);

    btnCancel = new QPushButton("Cancel");
    btnOpen = new QPushButton("Open");
    cmbType = new QComboBox();
    editDirectory = new QLineEdit();
    view = new QListView();
    model = new QDirModel();

    QVBoxLayout *vBoxMain = new QVBoxLayout();

    QHBoxLayout *lu_1 = new QHBoxLayout();
    QHBoxLayout *lu_2 = new QHBoxLayout();
    QHBoxLayout *lu_3 = new QHBoxLayout();

    QLabel *labelDir = new QLabel("Directory:");
    QLabel *labelType = new QLabel("Files of type:");

    QFontMetrics fmDir(labelDir->font());
    labelDir->setFixedWidth(fmDir.width(labelDir->text()));

    QFontMetrics fmType(labelType->font());
    labelType->setFixedWidth(fmType.width(labelType->text()));

    lu_1->addWidget(labelDir);
    lu_1->addWidget(editDirectory);
    lu_1->addWidget(btnOpen);

    lu_2->addWidget(labelType);
    lu_2->addWidget(cmbType);
    lu_2->addWidget(btnCancel);

    lu_3->addWidget(view);

    vBoxMain->addLayout(lu_3);
    vBoxMain->addLayout(lu_1);
    vBoxMain->addLayout(lu_2);

    selectLayout(vBoxMain);

    vBoxMain->setMargin(5);

    model->setFilter(QDir::Dirs | QDir::NoDot);


    view->setModel(model);
    view->setRootIndex(model->index(QDir::homePath()));

    editDirectory->setText(QDir::homePath());

    cmbType->addItem("Dirs");

    cmbType->setEnabled(false);

    btnOpen->setFixedSize(80, 25);

    btnCancel->setFixedSize(80, 25);


    connect(view, SIGNAL(doubleClicked(QModelIndex)),
            SLOT(changeDir(QModelIndex)));
    connect(btnCancel, SIGNAL(clicked(bool)),
            SLOT(close()));
    connect(btnOpen, SIGNAL(clicked(bool)),
            SLOT(open()));

}

void Dialog::changeDir(QModelIndex index)
{
    editDirectory->clear();
    editDirectory->setText(model->filePath(index));
    view->setRootIndex(index);
}

void Dialog::open()
{
    emit result(editDirectory->text() + "/");
    close();
}
