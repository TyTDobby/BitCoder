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
    TypeFlag Type;
} Flag;

typedef struct {
    std::string Name;
    std::string RootDir;
    std::vector<Flag> Flags;
    std::vector<std::string> Flags;


} ProjectOption;

class Project
{
public:
    Project();
};

}
