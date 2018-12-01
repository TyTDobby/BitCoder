#include "BitCoder.h"
#include "MessageBox.h"

#include <QVBoxLayout>
#include <QTextEdit>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QMenu>
#include <QMenuBar>
#include <QAction>

#include <iostream>
#include <fstream>
#include <string>

#include "Console.h"
#include "EditorBase.h"

BitCoder::BitCoder(FrameBase *parent)
    : FrameBase(parent)
{
    EditorBase *edit = new EditorBase();
    QVBoxLayout *boxMain = new QVBoxLayout();

    QMenuBar *menuBar = new QMenuBar(this);

    QMenu *fileMenu = new QMenu("File", menuBar);
    QMenu *editMenu = new QMenu("Edit", menuBar);

    QAction *acCreateFile = new QAction("Create file or project", fileMenu);
    QAction *acOpenFile = new QAction("Open file or project", fileMenu);

    QAction *acExit = new QAction("Exit", fileMenu);

    QHBoxLayout *hBoxTree = new QHBoxLayout();
    QVBoxLayout *vBoxEditCls = new QVBoxLayout();

    Console *console = new Console(this);

    treeProject = new TreeProject();

    vBoxEditCls->addWidget(edit);
    vBoxEditCls->addWidget(console);

    hBoxTree->addWidget(treeProject);
    hBoxTree->addLayout(vBoxEditCls);

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

    console->setFixedHeight(150);

    std::string fileSetting = "/home/alex/BitCoder-Deb000000000000000000000000000000000000000000000000000000000000ug/ex.json";

//    if (jsonFile.open(QIODevice::ReadOnly)) {
//        MessageBox *box = new MessageBox(TypeBox::FatalError, this);
//        box->showMessage(QString("File \"%1\" no exist").arg(fileSetting.c_str()));
//        connect(box, SIGNAL(fatalError()),
//                SLOT(close()));
//    }
//    else {
//        pt::ptree root;
//        try {
//            //read_json(fileSetting.c_str(), root);
//        }
//        catch (std::exception exp) {
//            MessageBox *box = new MessageBox(FatalError, this);
//            box->showMessage(QString("File \"%1\" no exist").arg(fileSetting.c_str()));
//            connect(box, SIGNAL(fatalError()),
//                    SLOT(close()));
//            box->show();
//            while (!isHidden());

//        }

//        write_json(std::cout, root);
//    }

    selectLayout(boxMain);
    setTitleText("BitCoder");
    /* Creating tmp files */
    if (!QFile::exists(QDir::temp().absoluteFilePath("STM.db"))) {
        qDebug() << "Creating STM database!";
        QFile::copy(":/db/STM.db", QDir::temp().absoluteFilePath("STM.db"));
    }

    setTitleFont(QFont("Courier", 11, QFont::Black));

    connect(acCreateFile, SIGNAL(triggered(bool)),
            SLOT(createFileOrPro()));
    connect(acOpenFile, &QAction::triggered,
            this, &BitCoder::openFolder);

    connect(acExit, SIGNAL(triggered(bool)),
            SLOT(close()));
    connect(treeProject, SIGNAL(openFile(QString)),
            edit, SLOT(setPlainText(QString)));

//    treeProject->addProject(Project::Project("123", "C:/Users/lymanets/123"));
}

BitCoder::~BitCoder()
{

}

void BitCoder::openFolder()
{
    Dialog *dl = new Dialog();
    connect(dl, &Dialog::result,
            this, [=](QString path) {
        Project::Project *pro = new Project::Project(path);
        pro->generateProject();
        this->treeProject->addProject(pro);
    });
    dl->show();

}

void BitCoder::createFileOrPro()
{
    CreateWidget *createWidget = new CreateWidget();
    connect(createWidget, SIGNAL(projectReady(Project::Project*)),
            treeProject, SLOT(addProject(Project::Project*)));
//    Dialog *dialog = new Dialog();
//    dialog->show();

    createWidget->show();
    //createWidget->setVisible(true);

}

