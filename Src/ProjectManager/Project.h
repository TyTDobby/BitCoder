#pragma once

#include <string>
#include <vector>
#include <iterator>

#include <QObject>
#include <QString>
#include <QDirIterator>
#include <QVector>
#include <QMap>
#include <QFileSystemWatcher>

#include "GenerateMakefile.h"
#include "Item.h"

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

struct SystemBuild{
    QString Name;
    QString Path;
    QStringList Flags;
} ;

typedef SystemBuild Compiler;
typedef SystemBuild Linker;

enum class ProjectCode
{
    NoState,
    CMakeFilesDontExist,
    Success,
    CouldnotProName

};

class ProjectState {
public:
    ProjectState()
    {
        this->msg = "";
        this->code = ProjectCode::NoState;
    }

    ProjectState(ProjectCode code, QString msg = "")
    {
        this->msg = msg;
        this->code = code;
    }

    QString msg;
    ProjectCode code;
};

class Project : public QObject
{
    Q_OBJECT
public:
    Project(QString RootDir);
    ~Project();

    ProjectState generateProject();
    ProjectState parsing();

    QStringList listDirs();
    QStringList listDirsWithAbsolutePath(QString path);
    QStringList listFiles();
    static QFileInfoList listDirContent(QString dir, QStringList strFilter);
    static bool removeDir(QString dir);
    void projectFileSystem();
    QFileInfoList findCMakeLists(QString dir);
    QFileInfo findCMakeListsRoot(QString dir);

    QStringList getCompilerFlags() const;
    void setCompilerFlags(const QStringList &value);

    QStringList getLinkerFlags() const;
    void setLinkerFlags(const QStringList &value);

    QString getOutputDir() const;
    void setOutputDir(const QString &value);

    QString getRootDir() const;
    void setRootDir(const QString &value);

    QString getTargetName() const;
    void setTargetName(const QString &value);

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

    Item *getRootItem() const;
    void setRootItem(const Item *value);

private:
    QString TargetName, OutputDir, LinkerScript;
    QFileInfo Root, RootFile;
    QStringList exception, dirs;
    Compiler compiler;
    Linker linker;
    TypeProject typeProject;
    DebugLevel debugLevel;
    QString coreSTM32;
    QStringList filter;
    QStringList files;
    Item *RootItem;
    QFileSystemWatcher *Watcher;

    void buildTree(Item *item, QString dir, QStringList strFilter);

signals:
    void changeProject(Project *);

};

}
