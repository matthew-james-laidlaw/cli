#pragma once

#include <iostream>
#include <optional>
#include <span>
#include <string>
#include <vector>

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

class CLI
{
private:

    std::string m_name;
    std::string m_description;
    std::string m_version;

    std::vector<Argument> m_arguments;
    std::vector<Option> m_options;
    std::vector<Command> m_subcommands;

    size_t m_arg_width;
    size_t m_opt_width;
    size_t m_cmd_width;

public:

    /**
     * @brief Create a new CLI object.
     */
    CLI(std::string_view name, std::string_view description, std::string_view version = "0.0.0");
    
    /**
     * @brief Register a new positional argument with the CLI.
     */
    auto AddArgument(std::string const& name, std::string const& description) -> void;

    /**
     * @brief Register a new optional argument with the CLI.
     */
    auto AddOption(std::optional<std::string> short_name, std::optional<std::string> long_name, std::string const& description) -> void;

    /**
     * @brief Register a new subcommand with the CLI.
     */
    auto AddSubcommand(std::string const& name, std::string const& description) -> void;

    /**
     * @brief Parse arguments from main.
     */
    auto Parse(int argc, char** argv) -> std::span<char*>;

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

private:

    template <typename Fn>
    auto PrintSection(std::string_view header, Fn printer) const -> void
    {
        std::cout << std::endl << header << ":" << std::endl << std::endl;
        printer();
    }

    auto PrintTitle() const -> void;
    auto PrintUsage() const -> void;
    auto PrintArguments() const -> void;
    auto PrintOptions() const -> void;
    auto PrintCommands() const -> void;
    
};

}
