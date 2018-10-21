#include "BitCoder.h"
#include "MessageBox.h"

#include <QVBoxLayout>
#include <QTextEdit>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QMenu>
#include <QMenuBar>

#include <iostream>
#include <fstream>
#include <string>

//#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/json_parser.hpp>

//namespace pt = boost::property_tree;

BitCoder::BitCoder(FrameBase *parent)
    : FrameBase(parent)
{
    QTextEdit *edit = new QTextEdit();
    QVBoxLayout *boxMain = new QVBoxLayout();

    QMenuBar *menuBar = new QMenuBar(this);

    QMenu *fileMenu = new QMenu("File", menuBar);
    QMenu *editMenu = new QMenu("Edit", menuBar);

    QAction *acCreateFile = new QAction("Create file or project");
    QAction *acOpenFile = new QAction("Open file or project");

    QAction *acExit = new QAction("Exit");

    QHBoxLayout *hBoxTree = new QHBoxLayout();

    treeProject = new TreeProject();

    hBoxTree->addWidget(treeProject);
    hBoxTree->addWidget(edit);

    boxMain->addWidget(menuBar);
    boxMain->addLayout(hBoxTree);

    /* Addind menubar and actions */
    fileMenu->addAction(acCreateFile);
    fileMenu->addAction(acOpenFile);
    fileMenu->addSeparator();
    fileMenu->addAction(acExit);

    acCreateFile->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    acOpenFile->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    acExit->setShortcut(QKeySequence(Qt::ALT + Qt::Key_F4));

    menuBar->addMenu(fileMenu);
    menuBar->addMenu(editMenu);



    std::string fileSetting = "/home/alex/BitCoder-Deb000000000000000000000000000000000000000000000000000000000000ug/ex.json";

//    if (jsonFile.open(QIODevice::ReadOnly)) {
//        MessageBox *box = new MessageBox(TypeBox::FatalError, this);
//        box->showMessage(QString("File \"%1\" no exist").arg(fileSetting.c_str()));
//        connect(box, SIGNAL(fatalError()),
//                SLOT(close()));
//    }
//    else {
//        pt::ptree root;
        try {
            //read_json(fileSetting.c_str(), root);
        }
        catch (std::exception exp) {
            MessageBox *box = new MessageBox(TypeBox::FatalError, this);
            box->showMessage(QString("File \"%1\" no exist").arg(fileSetting.c_str()));
            connect(box, SIGNAL(fatalError()),
                    SLOT(close()));
            box->show();
            while (!isHidden());

        }

//        write_json(std::cout, root);
//    }

    selectLayout(boxMain);
    setTitleText("BitCoder");
    setTitleIcon("/home/alex/Downloads/fold1.png");
    setTitleFont(QFont("Courier", 11, QFont::Black));

    connect(acCreateFile, SIGNAL(triggered(bool)),
            SLOT(createFileOrPro()));

    connect(acExit, SIGNAL(triggered(bool)),
            SLOT(close()));
    createFileOrPro();
}

BitCoder::~BitCoder()
{

}

void BitCoder::createFileOrPro()
{
    //CreateWidget *createWidget = new CreateWidget();

    Dialog *dialog = new Dialog();
    dialog->show();

    //createWidget->show();
    //createWidget->setVisible(true);

}

