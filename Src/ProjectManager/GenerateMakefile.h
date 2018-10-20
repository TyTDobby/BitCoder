#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>

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
    std::string name;
    std::string var;
} Var;

//typedef struct {
//    std::string name;
//    std::string value;
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

    void setBuildDir(std::string build);
    void setRootDir(std::string root);
    void setTargetName(std::string target);

    ToolIndex addTool(Tool tool);
    RuleIndex addRule(Rule rule);
    VariableIndex addVariable(Variable var);
    void addIfeq(std::string ifElse, std::string acIf, std::string acElse = "");

    Error generate();

    std::string getBuildDir();
    std::string getNameBuildDir();
    std::string &getRootDir();
    std::string getTargetName();

    Variable *getVariable(VariableIndex index);
    Rule *getRule(RuleIndex index);
    Tool *getTool(ToolIndex index);
private:
    Var target, build;
    std::string root;
    std::string ifeq;
    std::vector<Tool> tools;
    std::vector<Rule> rules;
    std::vector<Variable> vars;
};

class Rule
{
public:
    Rule(std::string name, std::string dep, std::string action);

    void addAction(std::string action);
    void addDep(std::string dep);

    void setName(std::string name);

    std::string &getName(void);
    std::string &getDep(void);
    std::string &getActions(void);

private:
    std::string name, dep, actions;
};

class Variable
{
public:
    Variable(std::string nameVar, std::string val);

    void addVal(std::string val);

    void setName(std::string nameVar);
    void setTypeVar(TypeVariable type);

    std::string &getName(void);
    std::string var(void);
    std::vector<std::string> &getVal(void);
    TypeVariable getTypeVar();

private:
    std::string nameVar;
    std::vector<std::string> val;
    TypeVariable typeVar;
};

class Tool
{
public:
    Tool(std::string name, std::string path);

    void setName(std::string name);
    void setPath(std::string path);

    std::string var(void);
    std::string &getName();
    std::string &getPath(void);

private:
    std::string name, path;
};

}

