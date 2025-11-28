#pragma once

#include "cli_types.h"

#include <iostream>
#include <string>
#include <vector>

namespace CLI
{

struct Info
{
    std::string m_name;
    std::string m_description;
    std::string m_version;

    std::vector<Argument> m_arguments;
    std::vector<Option> m_options;
    std::vector<Command> m_subcommands;

    size_t m_arg_width { 0 };
    size_t m_opt_width { 0 };
    size_t m_cmd_width { 0 };

    Info(std::string_view name, std::string_view description, std::string_view version = "0.0.0")
        : m_name(name), m_description(description), m_version(version)
    {}

    template <typename Fn>
    auto PrintSection(std::string_view header, Fn printer) const -> void
    {
        std::cout << '\n' << header << ":" << '\n' << '\n';
        printer();
    }

    auto PrintHelp() const -> void;
    auto PrintVersion() const -> void;

    auto PrintTitle() const -> void;
    auto PrintUsage() const -> void;
    auto PrintArguments() const -> void;
    auto PrintOptions() const -> void;
    auto PrintCommands() const -> void;

};

}
