#include "BitCoder.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BitCoder w;
    w.show();

    return a.exec();
}
