#pragma once

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QListView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QLineEdit>
#include <QFormLayout>
#include <QFileDialog>
#include <QLabel>
#include <QCheckBox>
#include <QTextEdit>
#include <QComboBox>
#include <QApplication>
#include <QProgressBar>

#include "DataBase.h"
#include "ListModel.h"
#include "Downloader.h"
#include "FrameBase.h"
#include "CreateProject.h"


#define CRYSTAL_NAME   0
#define PACKAGE        1
#define FREQUENCY      2
#define FLASH          3
#define E2PROM         4
#define RAM            5
#define DATASHEET      7
#define CORE           6

typedef struct {
    QString Seria;
    QStringList Crystals;
} STM32;

class CreateWidget : public FrameBase
{
    Q_OBJECT
public:
    CreateWidget(QWidget *parent = NULL);

    ~CreateWidget();
   void fileCreate();

private:
    QWidget *wgName, *wgCrystal, *wgFolders, *wgCompiler;
    QPushButton *btnCancel, *btnNext, *btnBack, *btnBrowse;// *btnCompilerPath;
    QListView *startView, *seriaView, *crystalView, *viewDrivers, *coreView;
    QLineEdit *editPath, *editName, *editInc, *editSrc, *editLibs, *editOther;
    CreateProject *crPro;
    QLabel *title;
    QTextEdit *editInfo;
    ListModel modelSeria, modelCrystal, model, modelDrivers, modelCore;
    DataBase dataBase;
    QStringList listCreate, listCoreSTM32, listSeria8, listSTM32, crystalInfo, libs, cubeHAL;
    Project::TypeProject typeProject;
    QCheckBox checkDefault;
    Downloader *downloader;
    QProgressBar *progress;
    QMap<QString, STM32> stm32;

    QString coreSTM32, selSeria, info, defaultDir;
    int count;
    bool select;
    bool isFile;

    void choose(const QModelIndex &index);
    void step(int index);
    void finish();

signals:
    void projectReady(Project::Project);

public slots:
    void selectionItem(const QModelIndex &index);
    void next();
    void back();
    void selectionCoreSTM32(const QModelIndex &index);
    void selectionSeria(const QModelIndex &index);
    void selectionCrystal(const QModelIndex &index);
    void browse();
    void pathProject(const QString &name);
    void selectLib(const QString &select);
    void download(const QByteArray &byte);
    void downloadProgress(int total);
    void browsePath(QString path);
    void done(Project::Project);

protected:
    void closeEvent(QCloseEvent *event);


};

