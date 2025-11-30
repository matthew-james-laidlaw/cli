#include <cli_parse_context.h>
#include <cli_validate.h>

#include <stdexcept>
#include <vector>

namespace CLI
{

ParseContext::ParseContext(std::span<char*> const& args, Registered const& registered)
    : m_args(args)
    , m_registered(registered)
{}

auto ParseContext::Parse() -> ParseResult
{
    while (!End())
    {
        if (m_registered.args.contains(*m_current))
        {
            m_result.args.push_back(ParseArgument());
        }
        else if (m_registered.opts.contains(*m_current))
        {
            m_result.opts.push_back(ParseOption());
        }
        else if (m_registered.cmds.contains(*m_current))
        {
            m_result.cmd = ParseCommand();
        }
        else
        {
            throw std::runtime_error("[error] unexpected argument");
        }
    }
}

auto ParseContext::ParseArgument() -> ParsedArg
{
    auto name = std::string(*m_current);
    ++m_current;

    auto value = ParseValue();

    return {.name = name, .value = value};
}

auto ParseContext::ParseOption() -> ParsedOpt
{
    auto name = std::string(*m_current);
    ++m_current;

    auto value = ParseValue();

    return {.name = name, .value = value};
}

auto ParseContext::ParseCommand() -> ParsedCmd
{
    ParsedCmd cmd;

    cmd.name = ParseIdentifier();

    while (!End())
    {
        if (m_registered.cmds.at(cmd.name).args.contains(*m_current))
        {
            cmd.args.push_back(ParseArgument());
        }
        else if (m_registered.cmds.at(cmd.name).opts.contains(*m_current))
        {
            cmd.opts.push_back(ParseOption());
        }
        else
        {
            throw std::runtime_error("[error] unexpected argument");
        }
    }

    return cmd;
}

auto ParseContext::ParseIdentifier() -> std::string
{
    if (!ValidName(*m_current))
    {
        throw std::runtime_error("[error] invalid identifier");
    }
    auto result = std::string(*m_current);
    ++m_current;
    return result;
}

auto ParseContext::ParseValue() -> std::string
{
    auto result = std::string(*m_current);
    ++m_current;
    return result;
}

auto ParseContext::End() const -> bool
{
    return m_current == m_args.end();
}

} // namespace CLI
