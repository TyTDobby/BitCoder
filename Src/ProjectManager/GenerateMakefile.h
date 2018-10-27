#pragma once

#include <QObject>
#include <QFile>
#include <QString>
#include <QVector>

namespace Makefile{

typedef enum {
    NoError,
    RootDirNotExist,
    NameEmpty,
    RootEmpty

} Error;

typedef enum TypeVariable{
    None,
    Assignment
} TypeVariable;

typedef struct {
    QString name;
    QString var;
} Var;

//typedef struct {
//    QString name;
//    QString value;
//} Variable;

typedef int ToolIndex;
typedef int RuleIndex;
typedef int VariableIndex;

class Generator;
class Tool;
class Rule;
class Variable;

class Generator
{
public:
    Generator();

    void setBuildDir(QString build);
    void setRootDir(QString root);
    void setTargetName(QString target);

    ToolIndex addTool(Tool tool);
    RuleIndex addRule(Rule rule);
    VariableIndex addVariable(Variable var);
    void addIfeq(QString ifElse, QString acIf, QString acElse = "");

    void addPHONY(Rule *rules);

    QString wildcard(QString pattern);
    QString addprefix(QString prefix, QString names);
    QString subst(QString from, QString to, QString text);
    QString echo(QString text);

    Error generate();

    QString getBuildDir();
    QString getNameBuildDir();
    QString &getRootDir();
    QString getTargetName();

    Variable *getVariable(VariableIndex index);
    Rule *getRule(RuleIndex index);
    Tool *getTool(ToolIndex index);

private:
    Var target, build;
    QString root;
    QString ifeq;
    QString PHONY;
    std::vector<Tool> tools;
    std::vector<Rule> rules;
    std::vector<Variable> vars;
};

class Rule
{
public:
    Rule(QString name, QString dep, QString action);

    void addAction(QString action);
    void addDep(QString dep);

    void setName(QString name);

    QString &getName(void);
    QString &getDep(void);
    QString &getActions(void);

private:
    QString name, dep, actions;
};

class Variable
{
public:
    Variable(QString nameVar, QString val = "");

    void addVal(QString val);

    void setName(QString nameVar);
    void setTypeVar(TypeVariable type);

    QString &getName(void);
    QString var(void);
    QVector<QString> &getVal(void);
    TypeVariable getTypeVar();

private:
    QString nameVar;
    QVector<QString> val;
    TypeVariable typeVar;
};

class Tool
{
public:
    Tool(QString name, QString path);

    void setName(QString name);
    void setPath(QString path);

    QString var(void);
    QString &getName();
    QString &getPath(void);

private:
    QString name, path;
};

}

