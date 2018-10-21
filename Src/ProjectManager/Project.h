#pragma once

#include <string>
#include <vector>

namespace Project {

typedef enum {
    FlagLinker,
    FlagCompiler
} TypeFlag;

typedef struct {
    std::string Name;
    std::string Value;
} Flag;

class Project
{
public:
    Project(std::string Name, std::string RootDir);

    std::vector<Flag> getCompilerFlags() const;
    void setCompilerFlags(const std::vector<Flag> &value);

    std::vector<Flag> getLinkerFlags() const;
    void setLinkerFlags(const std::vector<Flag> &value);

private:
    std::string Name, RootDir;
    std::vector<Flag> CompilerFlags, LinkerFlags;

};

}
