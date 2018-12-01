#include "Console.h"

#include <QDir>
#include <QApplication>
#include <QProcess>
#include <QTextBlock>

Console::Console(QWidget *parent) : QPlainTextEdit(parent)
{
    path = QDir::homePath();
    invite = QDir::home().dirName() + "#" + path + ": ";
//    setPlainText(invite);
    textCursor().insertText(invite);
}

void Console::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    setFocus();
}

void Console::mouseDoubleClickEvent(QMouseEvent *event)
{

}

void Console::keyPressEvent(QKeyEvent *event)
{
    if (event->key() >= 0x20 &&
            event->key() <= 0x7E &&
            (event->modifiers() == Qt::NoModifier || event->modifiers() == Qt::ShiftModifier)) {
        QPlainTextEdit::keyPressEvent(event);
    }
    if (event->key() == Qt::Key_Backspace &&
            event->modifiers() == Qt::NoModifier &&
            textCursor().positionInBlock() > invite.length()) {
        QPlainTextEdit::keyPressEvent(event);
    }
    if (event->key() == Qt::Key_Return && event->modifiers() == Qt::NoModifier) {
        if (textCursor().positionInBlock() == invite.length()) {
            return;
        }
        QProcess *proc = new QProcess();
        QString cmd = QString(textCursor().block().text().mid(invite.length()));
       // if (cmd == "clear") {
       //     clear();
       //     textCursor().insertText(invite);
       // }
        proc->start(cmd);
        while (proc->waitForFinished()) ;
        QString res = QString(proc->readAll());
        textCursor().insertText("\n" + res + "\n" + invite);


    }
}

void Console::contextMenuEvent(QContextMenuEvent *event)
{

}
