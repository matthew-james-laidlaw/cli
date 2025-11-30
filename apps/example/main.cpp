#include "cli_parser.h"

auto main(int argc, char const** argv) -> int
{
    auto cli = CLI::Parser("app", "an example app");
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
