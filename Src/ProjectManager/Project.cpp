#include "Project.h"

namespace Project
{

Project::Project(std::string Name, std::string RootDir)
{
    this->Name = Name;
    this->RootDir = RootDir;


}

std::vector<Flag> Project::getCompilerFlags() const
{
    return CompilerFlags;
}

void Project::setCompilerFlags(const std::vector<Flag> &value)
{
    CompilerFlags = value;
}

std::vector<Flag> Project::getLinkerFlags() const
{
    return LinkerFlags;
}

void Project::setLinkerFlags(const std::vector<Flag> &value)
{
    LinkerFlags = value;
}

}
