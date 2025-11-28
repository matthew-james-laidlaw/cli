#include "cli.h"
#include "cli_info.h"

#include <iomanip>

namespace CLI
{

auto Info::PrintHelp() const -> void
{
    PrintTitle();
    PrintUsage();

    if (!m_arguments.empty())
    {
        PrintSection("arguments", [&] { PrintArguments(); });
    }

    if (!m_options.empty())
    {
        PrintSection("options", [&] { PrintOptions(); });
    }

    if (!m_subcommands.empty())
    {
        PrintSection("commands", [&] { PrintCommands(); });
    }

    std::cout << std::endl;
}

auto Info::PrintVersion() const -> void
{
    std::cout << m_version << std::endl;
}

auto Info::PrintTitle() const -> void
{
    std::cout << m_name << " - " << m_description << std::endl;
}

auto Info::PrintUsage() const -> void
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

    std::cout << std::endl;
}

auto Info::PrintArguments() const -> void
{
    for (auto const& arg : m_arguments)
    {
        std::cout << "  " << std::left << std::setw(m_arg_width) << arg.name << "    " << arg.description << std::endl;
    }
}

auto Info::PrintOptions() const -> void
{
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

auto Info::PrintCommands() const -> void
{
    for (auto const& cmd : m_subcommands)
    {
        std::cout << "  " << std::left << std::setw(m_cmd_width) << cmd.name << "    " << cmd.description << std::endl;
    }
}

}
