#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <span>
#include <format>

namespace CLI
{

struct Argument
{
    std::string name;
    std::string description;
};

struct Option
{
    std::string short_name;
    std::string long_name;
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

public:

    CLI(std::string_view name, std::string_view description, std::string_view version = "0.0.0")
        : m_name(name), m_description(description), m_version(version)
    {}
    
    /**
     * @brief Register a new positional argument with the CLI.
     */
    auto AddArgument(std::string const& name, std::string const& description) -> void
    {
        m_arguments.push_back({name, description});
    }

    /**
     * @brief Register a new optional argument with the CLI.
     */
    auto AddOption(std::string const& short_name, std::string const& long_name, std::string const& description) -> void
    {
        m_options.push_back({short_name, long_name, description});
    }

    /**
     * @brief Register a new subcommand with the CLI.
     */
    auto AddSubcommand(std::string const& name, std::string const& description) -> void
    {
        m_subcommands.push_back({name, description});
    }

    /**
     * @brief Parse arguments from main.
     */
    auto Parse(int argc, char** argv) -> std::span<char*>
    {
        if (argc < 2)
        {
            throw std::runtime_error("[error] no arguments provided");
        }
        return std::span<char*>(argv + 1, argv + argc);
    }

    /**
     * @brief Print help text.
     */
    auto Help() const -> void
    {
        std::cout << m_name << " - " << m_description << std::endl;
        
        std::cout << std::endl;
        std::cout << "usage: " << m_name;
        
        if (!m_arguments.empty())
        {
            for (auto const& arg : m_arguments)
            {
                std::cout << " <" << arg.name << ">";
            }
        }

        if (!m_options.empty())
        {
            std::cout << " [options]";
        }

        if (!m_subcommands.empty())
        {
            std::cout << " [command]";
        }

        std::cout << std::endl;
    }

    /**
     * @brief Print version string.
     */
    auto Version() const -> void
    {
        std::cout << m_version << std::endl;
    }

protected:

    /**
     * Parse arguments from main as an iterable list.
     */
    auto Parse(std::span<char*> const& args) -> void
    {
        throw std::runtime_error("[error] not yet implemented");
    }

};

}

auto main(int argc, char** argv) -> int
{
    auto cli = CLI::CLI("app", "an example app");
    cli.AddArgument("arg-a", "a positional argument");
    cli.AddArgument("arg-b", "a positional argument");
    cli.AddArgument("arg-c", "a positional argument");
    cli.AddOption("-o", "--option", "an optional argument");
    cli.AddSubcommand("cmd", "a subcommand");
    cli.Help();
    return 0;
}
