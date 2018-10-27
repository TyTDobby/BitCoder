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
    viewHard = new QListView();
    model = new DirModel();
    modelHard = new DirModel();

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

    lu_3->addWidget(viewHard);
    lu_3->addWidget(view);

    vBoxMain->addLayout(lu_3);
    vBoxMain->addLayout(lu_1);
    vBoxMain->addLayout(lu_2);

    selectLayout(vBoxMain);

    vBoxMain->setMargin(5);

    model->setFilter(QDir::Dirs | QDir::Files | QDir::NoDot);
    model->setSorting(QDir::Type);

    view->setModel(model);
    view->setRootIndex(model->index(QDir::homePath()));

    viewHard->setFixedWidth(static_cast<int>(this->width() * 0.2));
    viewHard->setModel(modelHard);

    editDirectory->setText(QDir::homePath());

    cmbType->addItem("Dirs");

    cmbType->setEnabled(false);

    btnOpen->setFixedSize(80, 25);

    btnCancel->setFixedSize(80, 25);


    connect(view, SIGNAL(doubleClicked(QModelIndex)),
            SLOT(changeDir(QModelIndex)));
    connect(viewHard, SIGNAL(doubleClicked(QModelIndex)),
            SLOT(changeHard(QModelIndex)));
    connect(btnCancel, SIGNAL(clicked(bool)),
            SLOT(close()));
    connect(btnOpen, SIGNAL(clicked(bool)),
            SLOT(open()));
    connect(editDirectory, SIGNAL(textChanged(QString)),
            SLOT(changeText(QString)));

}

void Dialog::changeHard(QModelIndex index)
{
//    editDirectory->clear();
    editDirectory->setText(index.data().toString());
//    view->setRootIndex(index);
}

void Dialog::changeDir(QModelIndex index)
{
    editDirectory->clear();
    editDirectory->setText(model->filePath(index));
    view->setRootIndex(index);
}

void Dialog::changeText(QString text)
{
    QDir dir(text);
    if (dir.exists()) {
        view->setRootIndex(model->index(text));
    }
}

void Dialog::open()
{
    emit result(editDirectory->text() + "/");
    close();
}
