#include "cli_validate.h"

#include <algorithm>
#include <string>

namespace CLI
{

auto ValidName(std::string const& name) -> bool
{
    return !name.empty() && name.front() != '-' && name.back() != '-' &&
           std::ranges::all_of(name, IsName);
}

auto ValidShortName(std::string const& name) -> bool
{
    bool valid_length = name.length() == 2;
    bool valid_prefix = name[0] == '-';
    bool valid_chars = IsAlpha(name[1]);
    return valid_length && valid_prefix && valid_chars;
}

auto ValidLongName(std::string const& name) -> bool
{
    bool valid_length = name.length() > 4;
    bool valid_prefix = name.starts_with("--");
    bool valid_chars = std::ranges::all_of(name, IsName) && name[2] != '-' && name.back() != '-';
    return valid_length && valid_prefix && valid_chars;
}

auto ValidDescription(std::string const& description) -> bool
{
    return !description.empty();
}

auto IsAlpha(char c) -> bool
{
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

auto IsName(char c) -> bool
{
    return IsAlpha(c) || c == '-';
}

} // namespace CLI
