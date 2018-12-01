#pragma once

 __attribute__ ((unused)) static const char *typeData[] =
{
    "char", "void", "uint_8",
    "double", "uint_16" ,"uint_32",
    "float", "uchar", "int",
    "long", "short"
};

 __attribute__ ((unused)) static const char *keywordPatterns[] =
{
    "operator", "private", "protected", "public",
    "namespace", "volatile", "signed", "const",
    "static", "struct", "continue", "typedef",
    "typename", "union", "unsigned", "virtual",
    "class", "volatile", "extern", "for",
    "while", "switch", "case", "default",
    "const", "enum", "break", "if",
    "else", "return", "foreach", "goto",
    "sizeof", "this"
};

 __attribute__ ((unused)) static const char *preproc[] =
{
    "include", "define", "udef",
    "if", "ifdef", "ifndef",
    "else", "elif", "endif",
    "line", "error", "warning",
    "pragma"
};
