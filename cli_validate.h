#pragma once

#include <optional>
#include <string>

namespace CLI
{

auto ValidName(std::string const& name) -> bool;
auto ValidShortName(std::string const& name) -> bool;
auto ValidLongName(std::string const& name) -> bool;
auto ValidDescription(std::string const& description) -> bool;

auto IsAlpha(char c) -> bool;
auto IsName(char c) -> bool;

}
