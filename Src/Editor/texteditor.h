#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QTextCursor>
#include <QPainter>
#include <QTextBlock>
#include <QStringListModel>
#include <QCompleter>

#include "autocompleter.h"
#include "word.h"
#include "highlighter.h"
#include "listmodel.h"

QStringList sortName(QStringList list);

class TextEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    TextEditor(QWidget *parent = 0);
    ~TextEditor();

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);
    void updateCompleter();
    void replaceWord(QString value);

private:
    QWidget *lineNumberArea;
    HighLighter *highlighter;
    ListModel listModel;
    QCompleter *completer;
    QStringList listFun, listVar, listInclude, listIncStandard,
                listDefine, listType, list, standartFun;
    /*Списки стандартных ф-й*/
    QStringList listCtype, listLocale, listMath, listSetjmp,
                listSignal, listStdio, listStdlib, listString,
                listTime, listWchar, listWctype;
    int stop;
};
class LineNumberArea : public QWidget
{
public:
    LineNumberArea(TextEditor *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const Q_DECL_OVERRIDE {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    TextEditor *codeEditor;
};
#endif // TEXTEDITOR_H
