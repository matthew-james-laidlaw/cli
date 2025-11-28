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

    std::cout << '\n';
}

auto Info::PrintVersion() const -> void
{
    std::cout << m_version << '\n';
}

auto Info::PrintTitle() const -> void
{
    std::cout << m_name << " - " << m_description << '\n';
}

auto Info::PrintUsage() const -> void
{
    std::cout << '\n';
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

    std::cout << '\n';
}

auto Info::PrintArguments() const -> void
{
    for (auto const& arg : m_arguments)
    {
        std::cout << "  " << std::left << std::setw(static_cast<std::streamsize>(m_arg_width)) << arg.name << "    " << arg.description << '\n';
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
            std::cout << std::left << std::setw(static_cast<std::streamsize>(m_opt_width)) << *opt.long_name;
        }
        else
        {
            std::cout << std::string(m_opt_width, ' ');
        }

        std::cout << "    " << opt.description << '\n'; 
    }
}

auto Info::PrintCommands() const -> void
{
    for (auto const& cmd : m_subcommands)
    {
        std::cout << "  " << std::left << std::setw(static_cast<std::streamsize>(m_cmd_width)) << cmd.name << "    " << cmd.description << '\n';
    }
}

}
