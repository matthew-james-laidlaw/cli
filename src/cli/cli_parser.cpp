#include <cli_parse_context.h>
#include <cli_parser.h>
#include <cli_validate.h>

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

Parser::Parser(std::string_view name, std::string_view description, std::string_view version)
    : m_info(name, description, version)
{}

auto Parser::AddArgument(std::string const& name, std::string const& description) -> void
{
    if (!ValidName(name) || !ValidDescription(description))
    {
        throw std::runtime_error("[error] invalid argument");
    }

    m_info.m_arguments.push_back({.name = name, .description = description});
    m_info.m_arg_width = std::max(name.length(), m_info.m_arg_width);
    m_registered.args[name] = {.name = name};
}

auto Parser::AddOption(std::optional<std::string> short_name, std::optional<std::string> long_name,
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

    auto opt = RegOpt{.sname = short_name, .lname = long_name};
    if (short_name)
    {
        m_registered.opts[*short_name] = opt;
    }
    if (long_name)
    {
        m_registered.opts[*long_name] = opt;
    }
}

auto Parser::AddSubcommand(std::string const& name, std::string const& description) -> void
{
    m_info.m_subcommands.push_back({.name = name, .description = description});
    m_info.m_cmd_width = std::max(name.length(), m_info.m_cmd_width);

    m_registered.cmds[name] = {.name = name, .args = {}, .opts = {}};
}

auto Parser::Parse(int argc, char** argv) -> void
{
    if (argc < 2)
    {
        throw std::runtime_error("[error] no arguments provided");
    }
    Parse({argv + 1, static_cast<size_t>(argc - 1)});
}

auto Parser::Help() const -> void
{
    m_info.PrintHelp();
}

auto Parser::Version() const -> void
{
    m_info.PrintVersion();
}

auto Parser::Parse(std::span<char*> const& args) -> void
{
    auto ctx = ParseContext(args, m_registered);
    m_result = ctx.Parse();
}

} // namespace CLI
