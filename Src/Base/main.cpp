#include "BitCoder.h"
#include <QApplication>
#include "GenerateMakefile.h"
#include "QDirIterator"

QStringList listDirs(QString path, QStringList exception)
{
    QStringList list;
    if(path.lastIndexOf("/") != path.size() - 1) {
        path += "/";
    }

    QDirIterator itr(path, QDir::NoDotAndDotDot | QDir::Dirs, QDirIterator::Subdirectories);
    while(itr.hasNext()) {
        itr.next();
        QString dir = QString(itr.fileInfo().absoluteFilePath()).replace(0, path.size() - 1, "") + "/";
        bool isEx = false;
        for (auto &it : exception) {
            if (dir.indexOf(it) != -1) {
                isEx = true;
                break;
            }
        }
        if (!isEx) {
            list.push_back(dir.replace(0, 1, ""));
        }
    }
    list.push_back("");
    return list;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BitCoder w;
    w.show();

    return a.exec();
}
