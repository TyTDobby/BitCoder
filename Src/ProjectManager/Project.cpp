#include "Project.h"

#include <QApplication>
#include <QDebug>

namespace Project
{

Project::Project(QString NameTarget, QString RootDir)
{
    this->NameTarget = NameTarget;
    this->RootDir = RootDir;
    debugLevel = Level_4;
    RootItem = new ProjectItem();
}

QString Project::getCompilerName() const
{
    return compiler.Name;
}

void Project::setCompilerName(const QString &value)
{
    compiler.Name = value;
}

QString Project::getLinkerName() const
{
    return linker.Name;
}

void Project::setLinkerName(const QString &value)
{
    linker.Name = value;
}

QString Project::getCompilerPath() const
{
    return compiler.Path;
}

void Project::setCompilerPath(const QString &value)
{
    compiler.Path = value.lastIndexOf("/") != value.size() - 1 ? value + "/" : value;
}

QString Project::getLinkerPath() const
{
    return linker.Path;
}

void Project::setLinkerPath(const QString &value)
{
    linker.Path = value.lastIndexOf("/") != value.size() - 1 ? value + "/" : value;
}

QString Project::getCoreSTM32() const
{
    return coreSTM32;
}

void Project::setCoreSTM32(const QString &value)
{
    coreSTM32 = value;
}

QStringList Project::getFilter() const
{
    return filter;
}

void Project::setFilter(const QStringList &value)
{
    filter = value;
}

QStringList Project::getCompilerFlags() const
{
    return compiler.Flags;
}

void Project::setCompilerFlags(const QStringList &value)
{
    compiler.Flags = value;
}


QStringList Project::getLinkerFlags() const
{
    return linker.Flags;
}

void Project::setLinkerFlags(const QStringList &value)
{
    linker.Flags = value;
}

void Project::generateProject()
{
    Makefile::Generator make;

    make.setBuildDir(OutputDir);
    make.setRootDir(RootDir);
    make.setTargetName(NameTarget);

    QStringList dirs = listDirs();

    if (typeProject == Project_STM32) {
        compiler.Path = QApplication::applicationDirPath() + "/arm-gcc/bin/";
//        if (LinkerScript) {
            LinkerScript.replace(":/", "");
//        }



        QFile linkerFile(RootDir + LinkerScript);

        LinkerScript.replace("Linker", ":/Linker/LinkerScript");
        QFile tmpFile(LinkerScript);

        linkerFile.open(QIODevice::WriteOnly);
        tmpFile.open(QIODevice::ReadOnly);
        linkerFile.write(tmpFile.readAll());
        linkerFile.flush();
        linkerFile.close();

        if (compiler.Flags.empty()) {
            compiler.Flags << " -Wall"
                           << " -std=c99"
                           << " -std=c11"
                           << " -fdata-sections"
                           << " -ffunction-sections"
                           << " -mthumb"
                           << " -mcpu=" + coreSTM32;
        }
        for (auto &it : dirs) {
            compiler.Flags << " -I" + it;
        }
        Makefile::VariableIndex var_binpath = make.addVariable(Makefile::Variable("BINPATH",
                                                                                  compiler.Path));
        Makefile::VariableIndex var_build = make.addVariable(Makefile::Variable("BUILD_DIR",
                                                                                make.getBuildDir() + "/Release"));
        Makefile::VariableIndex var_cFlags = make.addVariable(Makefile::Variable("CFLAGS",
                                                                                 ""));
        Makefile::VariableIndex var_cppFlags = make.addVariable(Makefile::Variable("CPPFLAGS",
                                                                                   " -x c++ "));
        Makefile::VariableIndex var_asmFlags = make.addVariable(Makefile::Variable("ASMFLAGS",
                                                                                   ""));
        Makefile::VariableIndex var_lFlags = make.addVariable(Makefile::Variable("LFLAGS",
                                                                                 ""));
        Makefile::VariableIndex var_src = make.addVariable(Makefile::Variable("SRC"));
        Makefile::VariableIndex var_obj = make.addVariable(Makefile::Variable("OBJ"));
        Makefile::VariableIndex var_dirs = make.addVariable(Makefile::Variable("DIRS"));
        Makefile::VariableIndex var_build_dirs = make.addVariable(Makefile::Variable("BUILD_DIRS"));
        Makefile::VariableIndex var_linker_script = make.addVariable(Makefile::Variable("LINKER_SCRIPT", RootDir + LinkerScript));

        Makefile::ToolIndex tool_cc = make.addTool(Makefile::Tool("CC",
                                                                  make.getVariable(var_binpath)->var() + "arm-none-eabi-gcc"));
        Makefile::ToolIndex tool_as = make.addTool(Makefile::Tool("AS",
                                                                  make.getVariable(var_binpath)->var() + "arm-none-eabi-as"));
        Makefile::ToolIndex tool_sz = make.addTool(Makefile::Tool("SZ",
                                                                  make.getVariable(var_binpath)->var() + "arm-none-eabi-size"));
        Makefile::ToolIndex tool_cp = make.addTool(Makefile::Tool("CP",
                                                                  make.getVariable(var_binpath)->var() + "arm-none-eabi-objcopy"));
        Makefile::ToolIndex tool_hex = make.addTool(Makefile::Tool("HEX",
                                                                   make.getTool(tool_cp)->var() + " -O ihex "));
        Makefile::ToolIndex tool_bin = make.addTool(Makefile::Tool("BIN",
                                                                   make.getTool(tool_cp)->var() + " -O binary -S "));

        make.addRule(Makefile::Rule(make.getVariable(var_build_dirs)->var(),
                                    "",
                                    make.echo("> Creating $@") + "\n\t@mkdir $@\n"));

        Makefile::RuleIndex rule_elf = make.addRule(Makefile::Rule(make.getVariable(var_build)->var() + "/" +
                                                                   make.getTargetName() + ".elf",
                                                                   make.getVariable(var_obj)->var(),
                                                                   make.echo("> Generate $@")));
        Makefile::RuleIndex rule_hex = make.addRule(Makefile::Rule(make.getVariable(var_build)->var() + "/" +
                                                                   make.getTargetName() + ".hex",
                                                                   make.getRule(rule_elf)->getName(),
                                                                   make.echo("> Generate $@")));
        Makefile::RuleIndex rule_bin = make.addRule(Makefile::Rule(make.getVariable(var_build)->var() + "/" +
                                                                   make.getTargetName() + ".bin",
                                                                   make.getRule(rule_hex)->getName(),
                                                                   make.echo("> Generate $@")));
        Makefile::RuleIndex rule_c = make.addRule(Makefile::Rule(make.getVariable(var_build)->var() + "/%.o",
                                                                 "%.c",
                                                                 make.echo("> Compiling $@")));
        Makefile::RuleIndex rule_cpp = make.addRule(Makefile::Rule(make.getVariable(var_build)->var() + "/%.o",
                                                                   "%.cpp",
                                                                   make.echo("> Compiling $@")));
        Makefile::RuleIndex rule_cxx = make.addRule(Makefile::Rule(make.getVariable(var_build)->var() + "/%.o",
                                                                   "%.cxx",
                                                                   make.echo("> Compiling $@")));
        Makefile::RuleIndex rule_asm = make.addRule(Makefile::Rule(make.getVariable(var_build)->var() + "/%.o",
                                                                   "%.s",
                                                                   make.echo("> Compiling $@")));

        Makefile::RuleIndex rule_clean = make.addRule(Makefile::Rule("clean",
                                                                     "",
                                                                     make.echo("> Clean!")));


        Makefile::RuleIndex rule_all = make.addRule(Makefile::Rule("all",
                                                                   make.getVariable(var_build_dirs)->var() + " " + make.getRule(rule_bin)->getName(),
                                                                   make.echo("> Done!")));

        QString acCFile = "@" + make.getTool(tool_cc)->var() + " " + make.getVariable(var_cFlags)->var() + " -c $< -o $@";
        QString acCppFile = "@" + make.getTool(tool_cc)->var() + " " + make.getVariable(var_cppFlags)->var() + " -c $< -o $@";
        QString acAsmFile = "@" + make.getTool(tool_as)->var() + " " + make.getVariable(var_asmFlags)->var() + " -c $< -o $@";

        QString acElf = "@" + make.getTool(tool_cc)->var() + " " +
                make.getVariable(var_lFlags)->var() + " " +
                make.getVariable(var_obj)->var() + " -o $@";
        QString acHex = "@" + make.getTool(tool_hex)->var() + " $< $@";
        QString acBin = "@" + make.getTool(tool_bin)->var() + " -o $@\n\t";

        acBin += "@" + make.getTool(tool_sz)->var() + " " +
                make.getVariable(var_build)->var() + "/" +
                make.getRule(rule_elf)->getName();

        make.getRule(rule_c)->addAction(acCFile);
        make.getRule(rule_cpp)->addAction(acCppFile);
        make.getRule(rule_cxx)->addAction(acCppFile);
        make.getRule(rule_asm)->addAction(acAsmFile);

        make.getRule(rule_elf)->addAction(acElf);
        make.getRule(rule_hex)->addAction(acHex);
        make.getRule(rule_bin)->addAction(acBin);

        make.getRule(rule_clean)->addAction("rm -r " + make.getVariable(var_build)->var());

        QString level = " += -g" + QString::number(static_cast<int>(debugLevel == Level_4 ? Level_3 : debugLevel)) +
                        " -gdwarf-" + QString::number(static_cast<int>(debugLevel)) + " \n\t";

        QString acIf = make.getVariable(var_cFlags)->getName() + level;
        acIf += make.getVariable(var_cppFlags)->getName() + level;
        acIf += make.getVariable(var_asmFlags)->getName() + level;
        acIf += make.getVariable(var_build_dirs)->getName() + " := " + make.subst(make.getVariable(var_build)->var() + "/",
                                                                                  make.getBuildDir() + "/Debug/",
                                                                                  make.getVariable(var_build_dirs)->var()) + "\n\t";
        acIf += make.getVariable(var_obj)->getName() + " := " + make.subst(make.getVariable(var_build)->var() + "/",
                                                                           make.getBuildDir() + "/Debug/",
                                                                           make.getVariable(var_obj)->var()) + "\n\t";
        acIf += make.getVariable(var_build)->getName() + " := " + make.getBuildDir() + "/Debug";

        make.addIfeq("$(DEBUG), 1", acIf);

        for (auto &it : dirs) {
            make.getVariable(var_src)->addVal(make.wildcard(it + "*.c*"));
            make.getVariable(var_dirs)->addVal(it);
        }
        make.getVariable(var_src)->addVal(make.wildcard("*.c*"));

        make.getVariable(var_obj)->setTypeVar(Makefile::Assignment);
        make.getVariable(var_obj)->addVal("$(" + make.getVariable(var_src)->getName() + ":.c=.o)");
        make.getVariable(var_obj)->addVal("$(" + make.getVariable(var_obj)->getName() + ":.cpp=.o)");
        make.getVariable(var_obj)->addVal("$(" + make.getVariable(var_obj)->getName() + ":.cxx=.o)");

        make.getVariable(var_build_dirs)->addVal(make.getBuildDir() + "/");
        make.getVariable(var_build_dirs)->addVal(make.getVariable(var_build)->var() + "/");
        make.getVariable(var_build_dirs)->addVal(make.addprefix(make.getVariable(var_build)->var() + "/",
                                                                make.getVariable(var_dirs)->var()));

        for (auto &it : compiler.Flags) {
            make.getVariable(var_cFlags)->addVal(it);
        }

        for (auto &it : compiler.Flags) {
            make.getVariable(var_cppFlags)->addVal(it);
        }


        make.addPHONY(make.getRule(rule_clean));
        make.addPHONY(make.getRule(rule_all));

        files = this->listFiles();
        projectFileSystem();
    }

    make.generate();
}

QStringList Project::listDirs()
{

    QStringList list;
    if(RootDir.lastIndexOf("/") != RootDir.size() - 1) {
        RootDir += "/";
    }

    QDirIterator itr(RootDir, QDir::NoDotAndDotDot | QDir::Dirs, QDirIterator::Subdirectories);
    while(itr.hasNext()) {
        itr.next();
        QString dir = QString(itr.fileInfo().absoluteFilePath()).replace(0, RootDir.size() - 1, "") + "/";
        if (dir.indexOf(OutputDir) != -1) {
            continue;
        }
        list.push_back(dir.replace(0, 1, ""));
    }
    return list;
}

QStringList Project::listFiles()
{
    QStringList list;
    if(RootDir.lastIndexOf("/") != RootDir.size() - 1) {
        RootDir += "/";
    }

    QDirIterator itr(RootDir, filter, QDir::Files, QDirIterator::Subdirectories);

    while(itr.hasNext()) {
        itr.next();
        list << QString(itr.fileInfo().absoluteFilePath()).replace(0, RootDir.size(), "");
    }
    return list;
}

void Project::projectFileSystem()
{
    QStringList dirs = listDirs();
    dirs.push_front("");
    if(RootDir.lastIndexOf("/") != RootDir.size() - 1) {
        RootDir += "/";
    }

    for (auto &dir_it : dirs) {
        QString dirPath = RootDir + dir_it;
        QDirIterator itr(dirPath, filter, QDir::Files | QDir::Dirs);
        QStringList list;
        while(itr.hasNext()) {
            itr.next();

//            if(dir_it.isEmpty()) {

//            }
//            else {

//            }
                    list << QString(itr.fileInfo().absoluteFilePath()).replace(0, RootDir.size(), "");
        }
        RootItem->insertChildren(list);
    }
//    return list;
}

QString Project::getLinkerScript() const
{
    return LinkerScript;
}

void Project::setLinkerScript(const QString &value)
{
    LinkerScript = value;
}

void Project::setRootItem(const ProjectItem *value)
{
    *RootItem = *value;
}

ProjectItem *Project::getRootItem() const
{
    return RootItem;//static_cast<ProjectItem*>(&RootItem);
}

QString Project::getOutputDir() const
{
    return OutputDir;
}

void Project::setOutputDir(const QString &value)
{
    OutputDir = value;
}

QString Project::getRootDir() const
{
    return RootDir;
}

void Project::setRootDir(const QString &value)
{
    RootDir = value;
}

QString Project::getNameTarget() const
{
    return NameTarget;
}

void Project::setNameTarget(const QString &value)
{
    NameTarget = value;
}

QStringList Project::getDirs() const
{
    return dirs;
}

void Project::setDirs(const QStringList &value)
{
    dirs = value;
}

TypeProject Project::getTypeProject() const
{
    return typeProject;
}

void Project::setTypeProject(const TypeProject &value)
{
    typeProject = value;
}

DebugLevel Project::getDebugLevel() const
{
    return debugLevel;
}

void Project::setDebugLevel(const DebugLevel &value)
{
    debugLevel = value;
}

}
