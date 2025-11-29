#include "cli.h"
#include "cli_validate.h"

#include <algorithm>
#include <cstddef>
#include <optional>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>

using namespace std::string_literals;

namespace CLI
{

CLI::CLI(std::string_view name, std::string_view description, std::string_view version)
    : m_info(name, description, version)
{}

auto CLI::AddArgument(std::string const& name, std::string const& description) -> void
{
    if (!ValidName(name) || !ValidDescription(description))
    {
        throw std::runtime_error("[error] invalid argument");
    }

    m_info.m_arguments.push_back({.name = name, .description = description});
    m_info.m_arg_width = std::max(name.length(), m_info.m_arg_width);
}

auto CLI::AddOption(std::optional<std::string> short_name, std::optional<std::string> long_name,
                    std::string const& description) -> void
{
    if (!short_name && !long_name)
    {
        throw std::runtime_error("[error] optional argument must have at least one name");
    }

    if (short_name && !ValidShortName(*short_name))
    {
        throw std::runtime_error("[error] invalid short option");
    }

    if (long_name && !ValidLongName(*long_name))
    {
        throw std::runtime_error("[error] invalid long option");
    }

    m_info.m_options.push_back(
        {.short_name = short_name, .long_name = long_name, .description = description});

    if (long_name)
    {
        m_info.m_opt_width = std::max(long_name->length(), m_info.m_opt_width);
    }
}

auto CLI::AddSubcommand(std::string const& name, std::string const& description) -> void
{
    m_info.m_subcommands.push_back({.name = name, .description = description});
    m_info.m_cmd_width = std::max(name.length(), m_info.m_cmd_width);
}

auto CLI::Parse(int argc, char** argv) -> void
{
    if (argc < 2)
    {
        throw std::runtime_error("[error] no arguments provided");
    }
    Parse({argv + 1, static_cast<size_t>(argc - 1)});
}

auto CLI::Help() const -> void
{
    m_info.PrintHelp();
}

auto CLI::Version() const -> void
{
    m_info.PrintVersion();
}

auto CLI::Parse(std::span<char*> const& args) -> void
{
    (void)this;
    throw std::runtime_error("[error] not yet implemented");
}

} // namespace CLI
