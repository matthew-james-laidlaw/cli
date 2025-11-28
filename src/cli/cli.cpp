#include "cli.h"
#include "cli_validate.h"

#include <iomanip>

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

    m_info.m_arguments.push_back({name, description});

    if (name.length() > m_info.m_arg_width)
    {
        m_info.m_arg_width = name.length();
    }
}

auto CLI::AddOption(std::optional<std::string> short_name, std::optional<std::string> long_name, std::string const& description) -> void
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

    m_info.m_options.push_back({short_name, long_name, description});

    if (long_name.has_value() && long_name->length() > m_info.m_opt_width)
    {
        m_info.m_opt_width = long_name->length();
    }
}

auto CLI::AddSubcommand(std::string const& name, std::string const& description) -> void
{
    m_info.m_subcommands.push_back({name, description});

    if (name.length() > m_info.m_cmd_width)
    {
        m_info.m_cmd_width = name.length();
    }
}

auto CLI::Parse(int argc, char** argv) -> std::span<char*>
{
    if (argc < 2)
    {
        throw std::runtime_error("[error] no arguments provided");
    }
    return std::span<char*>(argv + 1, static_cast<size_t>(argc - 1));
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
    throw std::runtime_error("[error] not yet implemented");
}

}
