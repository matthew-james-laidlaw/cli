#pragma once

#include <cli_info.h>

#include <iostream>
#include <optional>
#include <span>
#include <string>
#include <vector>

namespace CLI
{

class Parser
{
private:

    Info m_info;

public:

    /**
     * @brief Create a new CLI object.
     */
    Parser(std::string_view name, std::string_view description, std::string_view version = "0.0.0");

    /**
     * @brief Register a new positional argument with the CLI.
     */
    auto AddArgument(std::string const& name, std::string const& description) -> void;

    /**
     * @brief Register a new optional argument with the CLI.
     */
    auto AddOption(std::optional<std::string> short_name, std::optional<std::string> long_name,
                   std::string const& description) -> void;

    /**
     * @brief Register a new subcommand with the CLI.
     */
    auto AddSubcommand(std::string const& name, std::string const& description) -> void;

    /**
     * @brief Parse arguments from main.
     */
    auto Parse(int argc, char** argv) -> void;

    /**
     * @brief Print help text.
     */
    auto Help() const -> void;

    /**
     * @brief Print version string.
     */
    auto Version() const -> void;

protected:

    /**
     * Parse arguments from main as an iterable list.
     */
    auto Parse(std::span<char*> const& args) -> void;
};

} // namespace CLI
