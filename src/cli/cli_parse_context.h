#pragma once

#include <optional>
#include <set>
#include <span>
#include <string>
#include <unordered_map>

/**
 *
 * Grammar:
 *
 * cli      ::= { argument | option } command
 * command  ::= identifier { argument | option }
 * argument ::= identifier value
 * option   ::= "-" identifier value | "--" identifier value
 *
 * identifier ::= alpha { alnum | "-" alnum }
 * alpha      ::= "a".."z" | "A".."Z"
 * alnum      ::= alpha | "0".."9"
 *
 */

namespace CLI
{

/**
 * @brief A registered positional argument.
 */
struct RegArg
{
    std::string name;
};

/**
 * @brief A registered optional argument.
 */
struct RegOpt
{
    std::optional<std::string> sname;
    std::optional<std::string> lname;
};

/**
 * @brief A registered subcommand.
 */
struct RegCmd
{
    std::string name;
    std::unordered_map<std::string, RegArg> args;
    std::unordered_map<std::string, RegOpt> opts;
};

/**
 * @brief A map of all registered elements and their sub-elements in the case of a subcommand.
 */
struct Registered
{
    std::unordered_map<std::string, RegArg> args;
    std::unordered_map<std::string, RegOpt> opts;
    std::unordered_map<std::string, RegCmd> cmds;
};

/**
 * @brief A parsed positional argument.
 */
struct ParsedArg
{
    std::string name;
    std::string value;
};

/**
 * @brief A parsed optional argument.
 */
struct ParsedOpt
{
    std::string name;
    std::string value;
};

/**
 * @brief A subcommand and its arguments.
 */
struct ParsedCmd
{
    std::string name;
    std::vector<ParsedArg> args;
    std::vector<ParsedOpt> opts;
};

/**
 * @brief A collection of all parsed arguments and subcommands.
 */
struct ParseResult
{
    std::vector<ParsedArg> args;
    std::vector<ParsedOpt> opts;
    std::optional<ParsedCmd> cmd;
};

class ParseContext
{
private:

    std::span<char*> const& m_args;
    std::span<char*>::const_iterator m_current;

    Registered const& m_registered;
    ParseResult m_result;

public:

    ParseContext(std::span<char*> const& args, Registered const& registered);

    auto Parse() -> ParseResult;

private:

    auto ParseArgument() -> ParsedArg;
    auto ParseOption() -> ParsedOpt;
    auto ParseCommand() -> ParsedCmd;
    auto ParseIdentifier() -> std::string;
    auto ParseValue() -> std::string;
    auto End() const -> bool;
};

} // namespace CLI
