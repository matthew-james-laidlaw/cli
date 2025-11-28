#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <span>
#include <format>
#include <optional>
#include <iomanip>

using namespace std::string_literals;

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

    CLI(std::string_view name, std::string_view description, std::string_view version = "0.0.0")
        : m_name(name), m_description(description), m_version(version), m_arg_width(0), m_opt_width(0), m_cmd_width(0)
    {}
    
    /**
     * @brief Register a new positional argument with the CLI.
     */
    auto AddArgument(std::string const& name, std::string const& description) -> void
    {
        m_arguments.push_back({name, description});

        if (name.length() > m_arg_width)
        {
            m_arg_width = name.length();
        }
    }

    /**
     * @brief Register a new optional argument with the CLI.
     */
    auto AddOption(std::optional<std::string> short_name, std::optional<std::string> long_name, std::string const& description) -> void
    {
        m_options.push_back({short_name, long_name, description});

        if (long_name.has_value() && long_name->length() > m_opt_width)
        {
            m_opt_width = long_name->length();
        }
    }

    /**
     * @brief Register a new subcommand with the CLI.
     */
    auto AddSubcommand(std::string const& name, std::string const& description) -> void
    {
        m_subcommands.push_back({name, description});

        if (name.length() > m_cmd_width)
        {
            m_cmd_width = name.length();
        }
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
        PrintTitle();
        PrintUsage();

        if (!m_arguments.empty())
        {
            PrintArguments();
        }

        if (!m_options.empty())
        {
            PrintOptions();
        }

        if (!m_subcommands.empty())
        {
            PrintCommands();
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

private:

    auto PrintTitle() const -> void
    {
        std::cout << m_name << " - " << m_description << std::endl;
    }

    auto PrintUsage() const -> void
    {
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
    }

    auto PrintArguments() const -> void
    {
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "arguments:" << std::endl;
        std::cout << std::endl;
        for (auto const& arg : m_arguments)
        {
            std::cout << "  " << std::left << std::setw(m_arg_width) << arg.name << "    " << arg.description << std::endl;
        }
    }

    auto PrintOptions() const -> void
    {
        std::cout << std::endl;
        std::cout << "options:" << std::endl;
        std::cout << std::endl;
        for (auto const& opt : m_options)
        {
            std::cout << "  ";
            if (opt.short_name.has_value())
            {
                std::cout << *opt.short_name;
                if (opt.long_name.has_value())
                {
                    std::cout << ", ";
                }
                else
                {
                    std::cout << "  ";
                }
            }
            else
            {
                std::cout << "    ";
            }

            
            if (opt.long_name.has_value())
            {
                std::cout << std::left << std::setw(m_opt_width) << *opt.long_name;
            }
            else
            {
                std::cout << std::string(m_opt_width, ' ');
            }

            std::cout << "    " << opt.description << std::endl; 
        }
    }

    auto PrintCommands() const -> void
    {
        std::cout << std::endl;
        std::cout << "commands:" << std::endl;
        std::cout << std::endl;
        for (auto const& cmd : m_subcommands)
        {
            std::cout << "  " << std::left << std::setw(m_cmd_width) << cmd.name << "    " << cmd.description << std::endl;
        }
    }
    
};

}

auto main(int argc, char** argv) -> int
{
    auto cli = CLI::CLI("app", "an example app");
    cli.AddArgument("a", "a positional argument");
    cli.AddArgument("ab", "a positional argument");
    cli.AddArgument("abc", "a positional argument");
    cli.AddOption("-o", "--option", "an optional argument");
    cli.AddOption("-x", {}, "an optional argument");
    cli.AddOption("-v", "--verbosity", "an optional argument");
    cli.AddOption({}, "--number", "an optional argument");
    cli.AddSubcommand("cmd", "a subcommand");
    cli.AddSubcommand("cmd2", "a subcommand");
    cli.Help();
    return 0;
}
