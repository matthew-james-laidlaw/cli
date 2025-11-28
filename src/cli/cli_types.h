#pragma once

#include <optional>
#include <string>

namespace CLI
{

struct Argument
{
    std::string name;
    std::string description;
};

struct Option
{
    std::optional<std::string> short_name;
    std::optional<std::string> long_name;
    std::string description;
};

struct Command
{
    std::string name;
    std::string description;
};

}
