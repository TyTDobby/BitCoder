#-------------------------------------------------
#
# Project created by QtCreator 2018-09-16T10:42:42
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BitCoder
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES +=  QT_DEBUG_PLUGINS
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#LIBS += \
#       -lboost_system\

#LIBS += -lclang

#INCLUDEPATH += /usr/lib/llvm-3.8/include
INCLUDEPATH += Src/Base/
INCLUDEPATH += Src/ProjectManager/
INCLUDEPATH += Src/Editor/

RESOURCES += qdarkstyle/style.qrc \
    Resources/Common.qrc

CONFIG += c++0x c++11

HEADERS += \
    Src/Base/BitCoder.h \
    Src/Base/DataBase.h \
    Src/Base/Dialog.h \
    Src/Base/Downloader.h \
    Src/Base/FrameBase.h \
    Src/Base/MessageBox.h \
    Src/ProjectManager/CreateWidget.h \
    Src/ProjectManager/GenerateMakefile.h \
    Src/ProjectManager/Icons.h \
    Src/ProjectManager/ListModel.h \
    Src/ProjectManager/TreeProject.h \
    Src/ProjectManager/Project.h \
    Src/Base/DirModel.h \
    Src/ProjectManager/CreateProject.h \
    Src/ProjectManager/Model.h \
    Src/ProjectManager/Item.h \
    Src/Base/Console.h \
    Src/Editor/EditorBase.h \
    Src/Editor/Autocomplete.h \
    Src/Editor/Highlighter.h \
    Src/Editor/word.h

SOURCES += \
    Src/Base/BitCoder.cpp \
    Src/Base/DataBase.cpp \
    Src/Base/Dialog.cpp \
    Src/Base/Downloader.cpp \
    Src/Base/FrameBase.cpp \
    Src/Base/main.cpp \
    Src/Base/MessageBox.cpp \
    Src/ProjectManager/CreateWidget.cpp \
    Src/ProjectManager/GenerateMakefile.cpp \
    Src/ProjectManager/ListModel.cpp \
    Src/ProjectManager/TreeProject.cpp \
    Src/ProjectManager/Project.cpp \
    Src/Base/DirModel.cpp \
    Src/ProjectManager/CreateProject.cpp \
    Src/ProjectManager/Model.cpp \
    Src/ProjectManager/Item.cpp \
    Src/Base/Console.cpp \
    Src/Editor/EditorBase.cpp \
    Src/Editor/Autocomplete.cpp \
    Src/Editor/Highlighter.cpp
