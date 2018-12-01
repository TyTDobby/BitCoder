#include "texteditor.h"
#include <QDebug>

QStringList sortName(QStringList list)
{
    QMap<QString, QString> map;
    foreach (const QString &str, list)
        map.insert(str.toLower(), str);

    return map.values();
}

TextEditor::TextEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);
    highlighter = new HighLighter(document());

    for(unsigned int i = 0; i < sizeof(keywordPatterns)/sizeof(*keywordPatterns); i++){
        list << keywordPatterns[i];
    }

    for(unsigned int i = 0; i < sizeof(typeData)/sizeof(*typeData); i++){
        listType << typeData[i];
    }

    for(unsigned int i = 0; i < sizeof(preproc)/sizeof(*preproc); i++){
        list << preproc[i];
    }

    listIncStandard << "assert.h" << "complex.h" << "ctype.h"    << "errno.h"
                    << "fenv.h"   << "float.h"   << "inttypes.h" << "iso646.h"
                    << "limits.h" << "locale.h"  << "math.h"     << "setjmp.h"
                    << "signal.h" << "stdarg.h"  << "stdbool.h"  << "stddef.h"
                    << "stdint.h" << "stdio.h"   << "stdlib.h"   << "string.h"
                    << "tgmath.h" << "threads.h" << "time.h"     << "wchar.h"
                    << "wctype.h";

    listCtype << "digittoint" << "isalnum"  << "isalpha" << "isascii"
              << "isblank"    << "iscntrl"  << "isdigit" << "isgraph"
              << "islower"    << "isprint"  << "ispunct" << "isspace"
              << "isupper"    << "isxdigit" << "toascii" << "tolower"
              << "toupper";

    listLocale << "localeconv" << "setlocale";

    listMath << "acos"  << "asin" << "atan"  << "atan2" << "atof"
             << "ceil"  << "cos"  << "cosh"  << "exp"   << "fabs"
             << "floor" << "fmod" << "frexp" << "ldexp" << "log"
             << "log10" << "modf" << "pow"   << "sin"   << "sinh"
             << "sqrt"  << "tan"  << "tanh";

    listSetjmp << "longjmp" << "setjmp";

    listSignal << "raise";

    listStdio << "clearerr" << "fclose"  << "feof"     << "ferror"   << "fflush"
              << "fgetc"    << "fgetpos" << "fgets"    << "fopen"    << "freopen"
              << "fdopen"   << "fprintf" << "fputc"    << "fputs"    << "fread"
              << "fscanf"   << "fseek"   << "fsetpos"  << "ftell"    << "fwrite"
              << "getc"     << "getchar" << "gets"     << "perror"   << "printf"
              << "fprintf"  << "sprintf" << "snprintf" << "putc"     << "putchar"
              << "fputchar" << "puts"    << "remove"   << "rename"   << "rewind"
              << "scanf"    << "fscanf"  << "sscanf"   << "vfscanf"  << "vscanf"
              << "vsscanf"  << "setbuf"  << "setvbuf"  << "tmpfile"  << "tmpnam"
              << "ungetc"   << "vprintf" << "vfprintf" << "vsprintf";

    listStdlib << "abort"   << "abs"    << "labs"    << "atexit" << "atof"
               << "atoi"    << "atol"   << "bsearch" << "calloc" << "div"
               << "ldiv"    << "exit"   << "free"    << "itoa"   << "getenv"
               << "ldiv"    << "ltoa"   << "malloc"  << "calloc" << "realloc"
               << "qsort"   << "rand"   << "srand"   << "strtod" << "strtol"
               << "strtoul" << "system";

    listString << "memchr"   << "memcmp"  << "memcpy"   << "memmove"
               << "memset"   << "strcat"  << "strncat"  << "strchr"
               << "strcmp"   << "strncmp" << "strcoll"  << "strcpy"
               << "strncpy"  << "strcspn" << "strerror" << "strlen"
               << "strpbrk"  << "strrchr" << "strspn"   << "strstr"
               << "strtok"   << "strxfrm";

    listTime << "asctime" << "clock"     << "ctime"  << "difftime"
             << "gmtime"  << "localtime" << "mktime" << "strftime"
             << "time";


    listWchar << "btowc"     << "fgetwc"    << "fgetws"    << "fputwc"  << "fputws"
              << "fwide"     << "fwprintf"  << "fwscanf"   << "mbrlen"  << "mbrtowc"
              << "mbsinit"   << "mbsrtowcs" << "swprintf"  << "swscanf" << "ungetwc"
              << "vfwprintf" << "vswprintf" << "vwprintf"  << "wcrtomb" << "wcscat"
              << "wcschr"    << "wcscmp"    << "wcscoll"   << "wcscpy"  << "wcscspn"
              << "wcsftime"  << "wcslen"    << "wcsncat"   << "wcsncmp" << "wcsncpy"
              << "wcspbrk"   << "wcsrchr"   << "wcsrtombs" << "wcsspn"  << "wcsstr"
              << "wcstod"    << "wcstok"    << "wcstol"    << "wcstoul" << "wcsxfrm"
              << "wctob"     << "wmemchr"   << "wmemcmp"   << "wmemcpy" << "wmemmove"
              << "wmemset"   << "wprintf"   << "wscanf";

    listWctype << "iswalnum"  << "iswalpha" << "iswcntrl" << "iswctype"
               << "iswdigit"  << "iswgraph" << "iswlower" << "iswprint"
               << "iswpunct"  << "iswspace" << "iswupper" << "iswxdigit"
               << "towctrans" << "towlower" << "towupper" << "wctrans"
               << "wctype";

    listFun += listCtype + listLocale + listMath + listSetjmp +
               listSignal + listStdio + listStdlib + listString +
               listTime + listWchar + listWctype;

    listFun = sortName(listFun);

    list += listType;
    list = sortName(list);
    list += listFun;

    completer = new AutoCompleter(this);
    listModel.setList(list);

    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWidget(this);
    completer->setModel(&listModel);

    setFont(QFont("Courier New", 12));

    setTabStopWidth(tabStopWidth() / 2);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
    stop = 0;

    for(unsigned int i = 0; i < sizeof(typeData)/sizeof(*typeData); i++){
        listType << typeData[i];
    }

    connect(this, SIGNAL(blockCountChanged(int)),
            this, SLOT(updateLineNumberAreaWidth(int)));

    connect(this, SIGNAL(updateRequest(QRect,int)),
            this, SLOT(updateLineNumberArea(QRect,int)));

    connect(this, SIGNAL(cursorPositionChanged()),
            this, SLOT(highlightCurrentLine()));

    connect(this, SIGNAL(textChanged()),
            SLOT(updateCompleter()));

    connect(completer, SIGNAL(activated(QString)),
            SLOT(replaceWord(QString)));




}

TextEditor::~TextEditor()
{

}

void TextEditor::replaceWord(QString value)
{
    QTextCursor cursor = textCursor();

    cursor.movePosition(QTextCursor::StartOfWord);
    cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);
    if((listFun.indexOf(QRegExp("^" + value)) >= 0) && value != ""){
        cursor.insertText(value + "();");
        cursor.movePosition(QTextCursor::Left);
        cursor.movePosition(QTextCursor::Left);
    }else{
        cursor.insertText(value);
    }
    setTextCursor(cursor);

}

void TextEditor::updateCompleter()
{
    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
    if(cursor.selectedText() != ")" || cursor.selectedText() != "\"" || cursor.selectedText() != "'"){
        cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor);
        if(cursor.selectedText() == "("){
            cursor.insertText("()");
            cursor.movePosition(QTextCursor::Left);
            setTextCursor(cursor);
        }else if(cursor.selectedText() == "\"" && stop == 0){
            stop += 1;
            cursor.insertText("\"\"");
            cursor.movePosition(QTextCursor::Left);
            setTextCursor(cursor);

        }else if(cursor.selectedText() == "'" && stop == 0){
            stop = 0;
            stop += 1;
            cursor.insertText("''");
            cursor.movePosition(QTextCursor::Left);
            setTextCursor(cursor);

        }else{
            stop = 0;
        }
    }
    cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::KeepAnchor);
    QString text = cursor.selectedText();
    if(text.startsWith("#include")){
        text.replace(QRegExp("\\s"), "");
        text.replace(QRegExp("<"), "\"");
        text.replace(QRegExp(">"), "\"");
        QString str;
        text.remove("#include");
        if((text.indexOf(".h") != -1 )
                || text.indexOf(".h\"") != -1){
            str = text;
            str.remove("\"");
            listInclude << str;
            listInclude.removeDuplicates();
            listInclude = sortName(listInclude);
        }
    }else if(text.startsWith("#define")){
        text.remove("#define ");
        QString str;
        if(text.endsWith(" ")){
            str = text;
            str.remove(" ");
        }
        listDefine << str;
        listDefine.removeDuplicates();
        listDefine = sortName(listDefine);
    }
    for(int i = 0; i < listType.length(); i++){
        QString str;
        if(text.startsWith(listType.at(i))){
            text.remove(listType.at(i) + " ");
            if(text.endsWith("(")){
                str = text;
                str.remove("(");
                listFun << str;
            }else if(text.indexOf("=") && text.indexOf(",") == -1){
                if(text.endsWith(";")){
                    str = text;
                }
                str.remove(" ");
                str.remove(str.indexOf("="), str.length());
                listVar << str;
            }else if(text.indexOf(",") && text.indexOf("=") == -1){
                if(text.endsWith(";")){
                    text.replace(";", ",");
                    for(int j = 0; j < text.length(); j++){
                        if(text.at(j) != ',')
                            str += text.at(j);
                        else{
                            str.remove(" ");
                            listVar << str;
                            str.clear();
                        }
                    }
                }
            }
        }
    }
    listVar.removeDuplicates();
    listFun.removeDuplicates();
    listVar = sortName(listVar);
    listFun = sortName(listFun);
}

int TextEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}

void TextEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void TextEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void TextEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void TextEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::gray).lighter(10);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void TextEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), QColor("#222"));

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(QColor("#ccc"));
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}
