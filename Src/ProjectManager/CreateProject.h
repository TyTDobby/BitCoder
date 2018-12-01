#pragma once

#include <QWidget>
#include <QProcess>
#include <QLayout>

#include <QDirIterator>
#include <QDirIterator>
#include <QVector>
#include <QProgressBar>

#include "GenerateMakefile.h"
#include "Project.h"
#include "FrameBase.h"

//namespace Project {

class CreateProject : public FrameBase
{
    Q_OBJECT
public:
    CreateProject(FrameBase *parent = NULL);

    void generation(Project::Project *project);

signals:
    void done(Project::Project*);

private:
    QProgressBar *bar;
};

//}
