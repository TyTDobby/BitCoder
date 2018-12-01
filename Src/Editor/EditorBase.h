#pragma once

#include <QWidget>
#include <QPlainTextEdit>
#include <QTextCursor>
#include <QPainter>
#include <QTextBlock>
#include <QStringListModel>
#include <QCompleter>
#include <QSortFilterProxyModel>

#include "Autocomplete.h"
#include "word.h"
#include "Highlighter.h"
#include "ListModel.h"

class EditorBase : public QPlainTextEdit
{
    Q_OBJECT
public:
    EditorBase(QWidget *parent = nullptr);
    ~EditorBase() override;

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) override;

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
    AutoCompleter *completer;
    QSortFilterProxyModel *proxyModel;
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
    LineNumberArea(EditorBase *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const override {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    EditorBase *codeEditor;
};
