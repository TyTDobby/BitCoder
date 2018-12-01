#include "Highlighter.h"

HighLighter::HighLighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;


    listColor << "#ff55ff" /*Строки, символы*/
              << "#59aa00" /*Функции*/
              << "#561eff" /*Имя класа*/
              << "#ffb028" /*Препроцессорные директивы*/
              << "#ffff55" /*Типы даных, служебные слова и тд*/;

    stringFormat.setForeground(QBrush(QColor(listColor.at(0))));
    rule.pattern = QRegExp("\".*\"");
    rule.format = stringFormat;
    highlightingRules.append(rule);

    quotationFormat.setForeground(QBrush(QColor(listColor.at(0))));
    rule.pattern = QRegExp("<.*>");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    charFormat.setForeground(QBrush(QColor(listColor.at(0))));
    rule.pattern = QRegExp("'.*'");
    rule.format = charFormat;
    highlightingRules.append(rule);

    functionFormat.setForeground(QBrush(QColor(listColor.at(1))));
    functionFormat.setFontWeight(99);
    rule.pattern = QRegExp("\\b[a-zA-Z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    classFormat.setForeground(QBrush(QColor(listColor.at(2))));
    rule.pattern = QRegExp("\\b[A-Z]\\B[a-zA-Z]+\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);

    for(unsigned int i = 0; i < sizeof(keywordPatterns)/sizeof(*keywordPatterns); i++){
        listKeywordPatterns << "\\b" + QString(keywordPatterns[i]) + "\\b";
    }

    for(unsigned int i = 0; i < sizeof(typeData)/sizeof(*typeData); i++){
        listKeywordPatterns << "\\b" + QString(typeData[i]) + "\\b";
    }
    listKeywordPatterns << "\\bdefault\\b";
    for(unsigned int i = 0; i < sizeof(preproc)/sizeof(*preproc); i++){
        listPreproc << "^#" + QString(preproc[i]);;
    }

    preprocFormat.setForeground(QBrush(QColor(listColor.at(3))));
    foreach (const QString &patt, listPreproc) {
        rule.pattern = QRegExp(patt);
        rule.format = preprocFormat;
        highlightingRules.append(rule);
    }

    keywordFormat.setForeground(QBrush(QColor(listColor.at(4))));
    keywordFormat.setFontWeight(QFont::Bold);
    foreach (const QString &pattern, listKeywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);

    }
    singleLineCommentFormat.setForeground(Qt::green);
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::green);

    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");

}

QStringList HighLighter::getListKeywordPatterns() const
{
    return listKeywordPatterns;
}

QStringList HighLighter::getListPreproc() const
{
    return listPreproc;
}

void HighLighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = commentStartExpression.indexIn(text);

    while (startIndex >= 0) {
        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
    }
}
