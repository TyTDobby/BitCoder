#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QDebug>

#include "word.h"

class HighLighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit HighLighter(QTextDocument *parent = 0);
    QStringList getListKeywordPatterns() const;

    QStringList getListPreproc() const;

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector <HighlightingRule> highlightingRules;

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;

    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
    QTextCharFormat preprocFormat;
    QTextCharFormat stringFormat;
    QTextCharFormat charFormat;

    QStringList listColor, listKeywordPatterns, listPreproc;
protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;
signals:

public slots:

};

#endif // HIGHLIGHTER_H
