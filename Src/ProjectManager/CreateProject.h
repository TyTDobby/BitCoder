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
    CreateProject(FrameBase *parent = nullptr);

    void generation(Project::ProjectInfo project);

signals:
    void done(Project::ProjectInfo);

private:
    QProgressBar *bar;
};

//}
