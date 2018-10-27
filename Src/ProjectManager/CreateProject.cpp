#include "CreateProject.h"
#include <QStyle>
#include <QApplication>
#include <QDesktopWidget>
#include <QThread>
//namespace Project
//{

CreateProject::CreateProject(FrameBase *parent) : FrameBase(parent)
{
    setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | windowFlags());

    hideBorder();
    setFixedSize(350, 40);
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight,
                                          Qt::AlignCenter,
                                          this->size(), QApplication::desktop()->screenGeometry()));

    QVBoxLayout *luMain = new QVBoxLayout();

    setLayout(luMain);

    bar = new QProgressBar();

    bar->setAlignment(Qt::AlignHCenter);
    luMain->addWidget(bar);

    bar->setTextVisible(true);

}

void CreateProject::generation(Project::ProjectInfo project)
{
    bar->setValue(0);
    bar->setFormat("Creating dirs");
    QDir dir;
    dir.mkdir(project.getRootDir());
    for (auto &it : project.getDirs()) {
        dir.mkdir(project.getRootDir() + "/" + it);
    }
    bar->setValue(50);
    bar->setFormat("Generating Makefile");

    project.generateProject();

    bar->setValue(100);
    bar->setFormat("Done");
    QThread::sleep(1);
    emit done(project);

}


//}
