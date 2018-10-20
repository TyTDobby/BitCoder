#include "CreateWidget.h"

#include <QLabel>
#include <QLayout>
#include <QRegExpValidator>

#include <fstream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "Dialog.h"

namespace pt = boost::property_tree;

Compiler addComnpiler (QString name, QString mask, QString path) {
    Compiler compiler;
    compiler.name = name;
    compiler.mask = mask;
    compiler.path = path;
    return compiler;
}

CreateWidget::CreateWidget(QWidget *parent) : FrameBase(parent)
{
    setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | windowFlags());
    setWindowButtons(Closed);

    defaultDir = QDir::homePath() + "/";

    count = 0;
    select = true;
    startView = new QListView(this);
    seriaView = new QListView(this);
    viewDrivers = new QListView(this);
    crystalView = new QListView(this);
    btnCancel = new QPushButton("Cancel", this);
    btnNext = new QPushButton("Choose", this);
    btnBack = new QPushButton("Back", this);
    btnBrowse = new QPushButton("Browse...", this);
    btnCompilerPath = new QPushButton("Browse...", this);
    wgName = new QWidget(this);
    wgCrystal = new QWidget(this);
    wgFolders = new QWidget(this);
    wgCompiler = new QWidget(this);
    editName = new QLineEdit(this);
    editPath = new QLineEdit(this);
    editInc = new QLineEdit(this);
    editLibs = new QLineEdit(this);
    editOther = new QLineEdit(this);
    editSrc = new QLineEdit(this);
    editCompilerPath = new QLineEdit(this);
    editCompilerName = new QLineEdit(this);
    title = new QLabel(this);
    editInfo = new QTextEdit(this);
    downloader = new Downloader(this);
    progress = new QProgressBar(this);
    QVBoxLayout *luMain = new QVBoxLayout();
    QHBoxLayout *luButtons = new QHBoxLayout();
    QVBoxLayout *luCentral = new QVBoxLayout();
    QHBoxLayout *luCrystal = new QHBoxLayout();
    QVBoxLayout *luFolders = new QVBoxLayout();
    QVBoxLayout *luCompiler = new QVBoxLayout();
    QFormLayout *luName = new QFormLayout();
    QHBoxLayout *lu = new QHBoxLayout();
    QVBoxLayout *lu_1 = new QVBoxLayout();
    QVBoxLayout *lu_2 = new QVBoxLayout();
    QFormLayout *lu_3 = new QFormLayout();
    QFormLayout *lu_4 = new QFormLayout();
    QHBoxLayout *lu_5 = new QHBoxLayout();
    QHBoxLayout *lu_6 = new QHBoxLayout();
    QHBoxLayout *lu_7 = new QHBoxLayout();
    QSpacerItem *spacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
    QSpacerItem *spacer_1 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Expanding);
    QLabel *seria = new QLabel("Seria", this);
    QLabel *crystalName = new QLabel("Crystal", this);
    QLabel *label = new QLabel("Library", this);
    QLabel *label_1 = new QLabel("Driver and tools", this);
    QComboBox *boxLib = new QComboBox(this);

    QString appPath = QApplication::applicationDirPath();

    selectLayout(luMain);

    luMain->setMargin(5);

    luMain->addLayout(luCentral);
    luMain->addLayout(luButtons);

    luButtons->addSpacerItem(spacer);
    luButtons->addWidget(btnBack);
    luButtons->addWidget(btnNext);
    luButtons->addWidget(btnCancel);

//    luCentral->addWidget(title);
    luCentral->addWidget(startView);
    luCentral->addWidget(wgName);
    luCentral->addWidget(wgCrystal);
    luCentral->addWidget(wgFolders);
    luCentral->addWidget(wgCompiler);
//    luCentral->addSpacerItem(spacer_1);
    luCentral->addWidget(progress);

    wgName->setLayout(luName);
    wgCrystal->setLayout(luCrystal);
    wgFolders->setLayout(luFolders);
    wgCompiler->setLayout(luCompiler);

    wgName->setVisible(false);
    wgCrystal->setVisible(false);
    wgFolders->setVisible(false);
    wgCompiler->setVisible(false);

    /* 1 step */
    lu->addWidget(editPath);
    lu->addWidget(btnBrowse);

    luName->addRow("Name: " , editName);
    luName->addRow("Path: ", lu);
    luName->addWidget(&checkDefault);

    /* 1 step */

    /* 2 step */
    luCrystal->addLayout(lu_2);
    luCrystal->addLayout(lu_1);
    luCrystal->addSpacerItem(spacer);

    lu_1->addWidget(editInfo);
    lu_1->addSpacerItem(spacer_1);

    lu_2->addWidget(seria);
    lu_2->addWidget(seriaView);
    lu_2->addWidget(crystalName);
    lu_2->addWidget(crystalView);
    /* 2 step */

    /* 3 step */
    luFolders->addLayout(lu_5);
    luFolders->addWidget(label);
    luFolders->addWidget(boxLib);
    luFolders->addWidget(label_1);
    luFolders->addWidget(viewDrivers);

    lu_5->addLayout(lu_3);
    lu_5->addLayout(lu_4);

    lu_3->addRow("Header", editInc);
    lu_3->addRow("Source", editSrc);

    lu_4->addRow("Library", editLibs);
    lu_4->addRow("Other", editOther);
    /* 3 step */

    /* 4 step */
    luCompiler->addLayout(lu_7);
    luCompiler->addLayout(lu_6);
    luCompiler->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Fixed, QSizePolicy::Expanding));

    lu_6->addWidget(new QLabel("Directory:"));
    lu_6->addWidget(editCompilerPath);
    lu_6->addWidget(btnCompilerPath);

    lu_7->addWidget(new QLabel("Name:"));
    lu_7->addWidget(editCompilerName);

    /* 4 step */

    title->setVisible(false);
    QFont font(title->font().family(), 10);
    font.setWeight(1000);
    title->setFont(font);

    listCreate << "New\nfile" << "Project\nSTM8" << "Project\nSTM32";
    QStringList listIcon;
    listIcon << appPath + "/Theme/office/image/NewFile.png"
             << appPath + "/Theme/office/image/ST.png"
             << appPath + "/Theme/office/image/ST.png";

    model.setIcons(listIcon);
    model.setList(listCreate);
    startView->setModel(&model);
    startView->setViewMode(QListView::IconMode);

    seriaView->setModel(&modelSeria);
    seriaView->setObjectName("view");
    seriaView->setFixedWidth(150);
    crystalView->setModel(&modelCrystal);
    crystalView->setObjectName("view");
    crystalView->setFixedWidth(150);

    viewDrivers->setModel(&modelDrivers);
    viewDrivers->setSelectionMode(QAbstractItemView::MultiSelection);

    info.append("Info:\n");

    editInfo->setStyleSheet("border: none;");
    editInfo->setReadOnly(true);
    editInfo->setFont(QFont(editInfo->font().family(), 10));
    editInfo->setFixedSize(500, 300);
    editInfo->setText(info);

    listSeria32 << "STM32L0" << "STM32L1" << "STM32L4" << "STM32F0" << "STM32F1"
                << "STM32F3" << "STM32F2" << "STM32F4" << "STM32F7" << "STM32H7";

    listSeria8 << "STM8AF" << "STM8AL" << "STM8L" << "STM8S";

    cubeHAL << "https://my.st.com/content/ccc/resource/technical/software/firmware/aa/4f/bd/e1/c0/cd/41/c5/stm32cubel0.zip/files/stm32cubel0.zip/_jcr_content/translations/en.stm32cubel0.zip"
            << "https://my.st.com/content/ccc/resource/technical/software/firmware/41/5f/8b/ee/f9/ac/48/55/stm32cubel1.zip/files/stm32cubel1.zip/_jcr_content/translations/en.stm32cubel1.zip"
            << "https://my.st.com/content/ccc/resource/technical/software/firmware/ca/20/a3/1a/24/48/42/24/stm32cubel4.zip/files/stm32cubel4.zip/jcr:content/translations/en.stm32cubel4.zip"
            << "https://my.st.com/content/ccc/resource/technical/software/firmware/b7/59/8e/1f/06/1f/49/ad/stm32cubef0.zip/files/stm32cubef0.zip/jcr:content/translations/en.stm32cubef0.zip"
            << "https://my.st.com/content/ccc/resource/technical/software/firmware/40/db/b8/d5/bd/a7/41/b1/stm32cubef1.zip/files/stm32cubef1.zip/jcr:content/translations/en.stm32cubef1.zip"
            << "https://my.st.com/content/ccc/resource/technical/software/firmware/bb/e8/99/00/99/f0/44/36/stm32cubef3.zip/files/stm32cubef3.zip/jcr:content/translations/en.stm32cubef3.zip"
            << "https://my.st.com/content/ccc/resource/technical/software/firmware/af/6b/52/18/26/d7/4f/72/stm32cubef2.zip/files/stm32cubef2.zip/jcr:content/translations/en.stm32cubef2.zip"
            << "https://my.st.com/content/ccc/resource/technical/software/firmware/06/64/ba/10/2e/ab/47/c8/stm32cubef4.zip/files/stm32cubef4.zip/jcr:content/translations/en.stm32cubef4.zip"
            << "https://my.st.com/content/ccc/resource/technical/software/firmware/18/40/6e/b0/44/f7/43/1d/stm32cubef7.zip/files/stm32cubef7.zip/jcr:content/translations/en.stm32cubef7.zip"
            << "https://my.st.com/content/ccc/resource/technical/software/firmware/group0/fd/9a/b6/df/a7/3d/41/0d/stm32cubeh7.zip/files/stm32cubeh7.zip/jcr:content/translations/en.stm32cubeh7.zip";

    crystalInfo << "";

    progress->setVisible(false);

    dataBase.connectToDataBase("STM");

    checkDefault.setText("Directory default");
    checkDefault.setVisible(false);

    btnBack->setVisible(false);

    editName->setValidator(new QRegExpValidator(QRegExp("^[a-zA-Z0-9]+$")));
    editName->setText("");
    editPath->setText(defaultDir);
    editInc->setText("Inc");
    editSrc->setText("Src");
    editLibs->setText("Libs");
    editOther->setText("Other");

    libs << "None(CMSIS)" << "StdPerish" << "Cube HAL";

#ifdef Q_OS_WIN
    //defaultDir = "C:/";
#endif

#ifdef Q_OS_LINUX
    QDir binDir("/usr/bin/");
#endif


    QStringList listFiles = binDir.entryList(QDir::Files);

    setTitleText("New file or project");

    boxLib->addItems(libs);

    connect(startView, SIGNAL(doubleClicked(QModelIndex)),
            SLOT(selectionItem(QModelIndex)));
    connect(btnNext, SIGNAL(clicked(bool)),
            SLOT(next()));
    connect(btnBack, SIGNAL(clicked(bool)),
            SLOT(back()));
    connect(btnCancel, SIGNAL(clicked(bool)),
            SLOT(close()));
    connect(seriaView, SIGNAL(clicked(QModelIndex)),
            SLOT(selectionSeria(QModelIndex)));
    connect(crystalView, SIGNAL(clicked(QModelIndex)),
            SLOT(selectionCrystal(QModelIndex)));
    connect(btnBrowse, SIGNAL(clicked(bool)),
            SLOT(browse()));
    connect(btnCompilerPath, SIGNAL(clicked(bool)),
            SLOT(browseCompiler()));
    connect(editName, SIGNAL(textChanged(QString)),
            SLOT(pathProject(QString)));
    connect(boxLib, SIGNAL(currentIndexChanged(QString)),
            SLOT(selectLib(QString)));
    connect(downloader, SIGNAL(done(QByteArray)),
            SLOT(download(QByteArray)));
    connect(downloader, SIGNAL(downloadProgress(int)),
            SLOT(downloadProgress(int)));
}

CreateWidget::~CreateWidget()
{

}

void CreateWidget::fileCreate()
{
    startView->setVisible(false);
    setTitleText("Location");
    btnNext->setText("Finish");
    wgName->setVisible(true);
}

void CreateWidget::choose(const QModelIndex &index)
{
    startView->setVisible(false);
    QString strSelect = index.data().toString();
    if(strSelect == listCreate.at(0)) {
        chooseCreate = File;
        fileCreate();
    }
    else {

        wgName->setVisible(true);
        checkDefault.setVisible(true);
        btnBack->setVisible(false);
        btnNext->setText("Next");
        if(strSelect == listCreate.at(1)) {
            chooseCreate = ProjectSTM8;
            modelSeria.setList(listSeria8);
        }
        else if(strSelect == listCreate.at(2)) {
            chooseCreate = ProjectSTM32;
            modelSeria.setList(listSeria32);
        }
    }
}

void CreateWidget::step(int index)
{
    switch(index) {
    case 0:
        wgName->setVisible(true);
        setTitleText("Location");
        wgCrystal->setVisible(false);
        wgFolders->setVisible(false);
        wgCompiler->setVisible(false);
        btnBack->setVisible(false);
        break;
    case 1:
        wgName->setVisible(false);
        wgCrystal->setVisible(true);
        setTitleText("Crystal");
        wgFolders->setVisible(false);
        wgCompiler->setVisible(false);
        btnBack->setVisible(true);
        btnNext->setText("Next");
        break;
    case 2:
        wgName->setVisible(false);
        wgCrystal->setVisible(false);
        setTitleText("Folders");
        wgFolders->setVisible(true);
        wgCompiler->setVisible(false);
        btnNext->setText("Next");
        break;
    case 3:
        wgName->setVisible(false);
        wgCrystal->setVisible(false);
        setTitleText("Compiler");
        wgFolders->setVisible(false);
        wgCompiler->setVisible(true);
        btnNext->setText("Finish");

        if (chooseCreate == ProjectSTM32) {
            editCompilerName->setText("arm-none-eabi-gcc");
        }
        else if (chooseCreate == ProjectSTM8) {
            editCompilerName->setText("sdcc");
        }

        break;
    case 4:
        finish();
        break;

    }
}

void CreateWidget::finish()
{
    progress->setVisible(true);
    QDir dirProject, dirLibs, dirOther, dirInc, dirSrc;
    dirProject.mkdir(editPath->text());
    dirLibs.mkdir(editPath->text() + "/" + editLibs->text());
    dirOther.mkdir(editPath->text() + "/" + editOther->text());
    dirInc.mkdir(editPath->text() + "/" + editInc->text());
    dirSrc.mkdir(editPath->text() + "/" + editSrc->text());
    progress->setValue(20);

//    std::fstream jsonFile;
//    jsonFile.open(QString(editPath->text() + "/build.json").toStdString(), std::ios::trunc | std::ios::out);

//    pt::ptree json;

//    json.put("Target", editName->text().toStdString());
//    json.put("Includes", editName->text().toStdString());


//    write_json(jsonFile, json);
}

void CreateWidget::selectionItem(const QModelIndex &index)
{
    choose(index);
    next();
}

void CreateWidget::next()
{
    if(select) {
        choose(startView->currentIndex());
        select = false;
    }
    else {
        if (!editName->text().isEmpty()) {
            if(chooseCreate != File) {
                count++;
                if(count >= 3)
                    count = 3;
                step(count);
            }
            else {
                choose(startView->currentIndex());
            }
        }
    }
}

void CreateWidget::back()
{
    count--;
    if(count < 0)
        count = 0;
    step(count);
}

void CreateWidget::selectionSeria(const QModelIndex &index)
{
    selSeria = index.data().toString();
    modelCrystal.setList(dataBase.readSeria(selSeria));
}

void CreateWidget::selectionCrystal(const QModelIndex &index)
{
    QString sel = index.data().toString();
    crystalInfo = dataBase.readCryatslInfo(sel, selSeria);
    info.clear();
    info.append("Name: " + crystalInfo.at(CRYSTAL_NAME) + "\n");
    info.append("Package: " + crystalInfo.at(PACKAGE) + "\n");
    if(!sel.startsWith("STM8")) {
        info.append("Core: " + crystalInfo.at(CORE) + "\n");
    }
    info.append("Frequency: " + crystalInfo.at(FREQUENCY) + " MHz\n");
    info.append("RAM: " + crystalInfo.at(RAM) + " kB\n");
    info.append("FLASH: " + crystalInfo.at(FLASH) + " kB\n");

    if(crystalInfo.at(E2PROM) != "-") {
        info.append("E2PROM: " + crystalInfo.at(E2PROM) + " B");
    }
    else {
        info.append("E2PROM: -");
    }
    editInfo->clear();
    editInfo->setText(info);
}

void CreateWidget::browse()
{
    Dialog *dialog = new Dialog();
    dialog->show();
    connect(dialog, SIGNAL(result(QString)),
            SLOT(browsePath(QString)));
}

void CreateWidget::browseCompiler()
{
    Dialog *dialog = new Dialog();
    dialog->show();
    connect(dialog, SIGNAL(result(QString)),
            editCompilerPath, SLOT(setText(QString)));
}

void CreateWidget::pathProject(const QString &name)
{
    QString text = editPath->text();
    text.replace(text.lastIndexOf('/'), text.size() - 1, "/" + name);
    editPath->setText(text);
}

void CreateWidget::selectLib(const QString &select)
{
    if(select == libs.at(0)) {/*None(CMSIS)*/

    }
    else if(select == libs.at(1)) {/*StdPerish*/

    }
    else if(select == libs.at(2)) {/*Cube HAL*/
        //downloader->setUrl(QUrl(cubeHAL.at(seriaView->currentIndex().row())));
    }
}

void CreateWidget::download(const QByteArray &byte)
{

    QFile file(QApplication::applicationDirPath() + "/Firmware/" + seriaView->currentIndex().data().toString() + ".zip");
    if(file.open(QIODevice::WriteOnly)) {
        file.write(byte);
        file.close();
    }
//    progress->setVisible(false);
//    qDebug() << "File created!";

}

void CreateWidget::downloadProgress(int total)
{
    progress->setVisible(true);
    progress->setValue(total);
}

//void CreateWidget::compilerPath(QString &value)
//{

//}

void CreateWidget::browsePath(QString path)
{
    editPath->setText(path + editName->text());
}

void CreateWidget::closeEvent(QCloseEvent *event)
{
    QWidget::closeEvent(event);
    dataBase.closeDataBase();
}

