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



#define CRYSTAL_NAME   0
#define PACKAGE        1
#define FREQUENCY      2
#define FLASH          3
#define E2PROM         4
#define RAM            5
#define DATASHEET      7
#define CORE           6

typedef struct {
    QString name;
    QString mask;
    QString path;
} Compiler;



class CreateWidget : public FrameBase
{
    Q_OBJECT
public:
    CreateWidget(QWidget *parent = nullptr);

    ~CreateWidget();
   void fileCreate();

private:
    enum Create{
        File,
        ProjectSTM8,
        ProjectSTM32
    };
    QWidget *wgName, *wgCrystal, *wgFolders, *wgCompiler;
    QPushButton *btnCancel, *btnNext, *btnBack, *btnBrowse, *btnCompilerPath;
    QListView *startView, *seriaView, *crystalView, *viewDrivers;
    QLineEdit *editPath, *editName, *editInc, *editSrc, *editLibs, *editOther, *editCompilerPath, *editCompilerName;
    QLabel *title;
    QTextEdit *editInfo;
    ListModel modelSeria, modelCrystal, model, modelDrivers;
    DataBase dataBase;
    QStringList listCreate, listSeria32, listSeria8, crystalInfo, libs, cubeHAL;
    Create chooseCreate;
    QCheckBox checkDefault;
    Downloader *downloader;
    QProgressBar *progress;
    QVector<Compiler> compilers;

    QString selSeria, info, defaultDir;
    int count;
    bool select;

private:
    void choose(const QModelIndex &index);
    void step(int index);
    void finish();

signals:

public slots:
    void selectionItem(const QModelIndex &index);
    void next();
    void back();
    void selectionSeria(const QModelIndex &index);
    void selectionCrystal(const QModelIndex &index);
    void browse();
    void pathProject(const QString &name);
    void selectLib(const QString &select);
    void download(const QByteArray &byte);
    void downloadProgress(int total);
//    void compilerPath(QString &value);
    void browsePath(QString path);
    void browseCompiler();

protected:
    void closeEvent(QCloseEvent *event);


};

