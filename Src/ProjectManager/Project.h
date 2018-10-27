#pragma once

#include <string>
#include <vector>

#include <QDirIterator>
#include <QDirIterator>
#include <QVector>

#include "GenerateMakefile.h"


namespace Project {

typedef enum {
    FlagLinker,
    FlagCompiler
} TypeFlag;

typedef enum {
    Project_Empty,
    Project_STM32,
    Project_C,
    Project_CPP,
    Project_STM8
} TypeProject;

typedef enum {
    Level_1 = 1,
    Level_2 = 2,
    Level_3 = 3,
    Level_4 = 4
} DebugLevel;

typedef struct {
    QString Name;
    QString Value;
} Flag;

struct SystenBuild{
    QString Name;
    QString Path;
    QStringList Flags;
} ;

typedef SystenBuild Compiler;
typedef SystenBuild Linker;

class ProjectInfo
{
public:
    ProjectInfo(QString NameTarget, QString RootDir);


    void generateProject();

    QStringList getListDirs();
    QStringList getListFiles();

    QStringList getCompilerFlags() const;
    void setCompilerFlags(const QStringList &value);

    QStringList getLinkerFlags() const;
    void setLinkerFlags(const QStringList &value);

    QString getOutputDir() const;
    void setOutputDir(const QString &value);

    QString getRootDir() const;
    void setRootDir(const QString &value);

    QString getNameTarget() const;
    void setNameTarget(const QString &value);

    QStringList getDirs() const;
    void setDirs(const QStringList &value);

    TypeProject getTypeProject() const;
    void setTypeProject(const TypeProject &value);

    DebugLevel getDebugLevel() const;
    void setDebugLevel(const DebugLevel &value);

    QString getCompilerName() const;
    void setCompilerName(const QString &value);

    QString getLinkerName() const;
    void setLinkerName(const QString &value);

    QString getCompilerPath() const;
    void setCompilerPath(const QString &value);

    QString getLinkerPath() const;
    void setLinkerPath(const QString &value);

    QString getCoreSTM32() const;
    void setCoreSTM32(const QString &value);

    QStringList getFilter() const;
    void setFilter(const QStringList &value);

    QString getLinkerScript() const;
    void setLinkerScript(const QString &value);

private:
    QString NameTarget, RootDir, OutputDir, LinkerScript;
    QStringList exception, dirs;
    Compiler compiler;
    Linker linker;
    TypeProject typeProject;
    DebugLevel debugLevel;
    QString coreSTM32;
    QStringList filter;
    QStringList files;


};

}
