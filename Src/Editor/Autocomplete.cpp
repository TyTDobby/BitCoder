#include "Autocomplete.h"

AutoCompleter::AutoCompleter(QObject *parent):
    QCompleter(parent)
{
}

AutoCompleter::~AutoCompleter()
{
}

bool AutoCompleter::eventFilter(QObject *o, QEvent *e)
{
    if(widget()->inherits("QPlainTextEdit") && e->type() == QEvent::KeyPress){
        QKeyEvent *k = static_cast<QKeyEvent*>(e);
        switch (k->key()) {
        case Qt::Key_Space:
            if(k->modifiers().testFlag(Qt::ControlModifier)){
                QPlainTextEdit *edit = qobject_cast<QPlainTextEdit*>(widget());
                QTextCursor cursor = edit->textCursor();
                cursor.movePosition(QTextCursor::StartOfWord, QTextCursor::KeepAnchor);
                if(cursor.selectedText().length() >= 0){
                    show(cursor, edit);
                }
                return true;
            }
            break;
        case Qt::Key_Enter:
        case Qt::Key_Return:
        case Qt::Key_Tab:
            if(popup()->isVisible()){
                popup()->hide();
                if(popup()->currentIndex().isValid()){
                    emit activated(popup()->currentIndex());
                    emit activated(popup()->currentIndex().data(completionRole()).toString());
                }
                return true;
            }
            //QPlainTextEdit *edit = qobject_cast<QPlainTextEdit*>(widget());
            //QTextCursor cursor = edit->textCursor();
            //cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::KeepAnchor);
//            if(cursor.selectedText().endsWith("{")){
//                cursor.insertText("{\n}");
//                cursor.movePosition(QTextCursor::Up);
//                cursor.movePosition(QTextCursor::Up);
//                cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::KeepAnchor);
//                cursor.insertText("{\t");
//                edit->setTextCursor(cursor);
//            }
            break;
        }
    }
    return QCompleter::eventFilter(o, e);
}

void AutoCompleter::replaceWord(QString value)
{
    QPlainTextEdit *edit = qobject_cast<QPlainTextEdit*>(widget());
    QTextCursor cursor = edit->textCursor();

    cursor.movePosition(QTextCursor::StartOfWord);
    cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);
    cursor.insertText(value);
    edit->setTextCursor(cursor);

}

void AutoCompleter::show(QTextCursor &cursor, QPlainTextEdit *edit)
{
    setCompletionPrefix(cursor.selectedText());
    QRect rect = QRect(edit->cursorRect().bottomLeft(), QSize(100, 5));
    complete(rect);
}
