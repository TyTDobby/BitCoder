#ifndef AUTOCOMPLETER_H
#define AUTOCOMPLETER_H

#include <QCompleter>
#include <QEvent>
#include <QKeyEvent>
#include <QAbstractItemView>
#include <QTextCursor>
#include <QPlainTextEdit>
#include <QDebug>
#include <QStringListModel>

class AutoCompleter : public QCompleter
{
    Q_OBJECT
public:
    AutoCompleter(QObject *parent = 0);
    ~AutoCompleter();

    void show(QTextCursor &cursor, QPlainTextEdit *edit);
    bool eventFilter(QObject *o, QEvent *e);

public slots:
    void replaceWord(QString value);

};

#endif // AUTOCOMPLETER_H
