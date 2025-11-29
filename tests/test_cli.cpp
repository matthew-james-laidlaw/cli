#include <gtest/gtest.h>

#include <cli_parser.h>

using namespace CLI;

TEST(TestCli, HelpTitle)
{
    auto cli = Parser("app", "an example app");

    ::testing::internal::CaptureStdout();
    cli.Help();
    auto help = ::testing::internal::GetCapturedStdout();

    ASSERT_EQ(help, "app - an example app\n\nusage: app\n\n");
}

TEST(TestCli, HelpArguments)
{
    auto cli = Parser("app", "an example app");

    cli.AddArgument("arg-a", "first positional arg");
    cli.AddArgument("arg-b", "second positional arg");

    ::testing::internal::CaptureStdout();
    cli.Help();
    auto help = ::testing::internal::GetCapturedStdout();

    ASSERT_TRUE(help.contains("app <arg-a> <arg-b>\n\n") && help.contains("arguments:\n\n") &&
                help.contains("  arg-a    first positional arg\n") &&
                help.contains("  arg-b    second positional arg\n\n"));
}

TEST(TestCli, HelpOptions)
{
    auto cli = Parser("app", "an example app");

    cli.AddOption("-a", "--alpha", "has both names");
    cli.AddOption({}, "--beta", "has only long name");
    cli.AddOption("-c", {}, "has only short name");

    ::testing::internal::CaptureStdout();
    cli.Help();
    auto help = ::testing::internal::GetCapturedStdout();

    ASSERT_TRUE(help.contains("app [options]\n\n") && help.contains("options:\n\n") &&
                help.contains("  -a, --alpha    has both names\n") &&
                help.contains("      --beta     has only long name\n") &&
                help.contains("  -c             has only short name\n\n"));
}

TEST(TestCli, HelpCommands)
{
    auto cli = Parser("app", "an example app");

    cli.AddSubcommand("cmd-a", "a subcommand");
    cli.AddSubcommand("cmd-b", "another subcommand");

    ::testing::internal::CaptureStdout();
    cli.Help();
    auto help = ::testing::internal::GetCapturedStdout();

    ASSERT_TRUE(help.contains("app [command]\n\n") && help.contains("commands:\n\n") &&
                help.contains("  cmd-a    a subcommand\n") &&
                help.contains("  cmd-b    another subcommand\n\n"));
}

TEST(TestCli, HelpCombined)
{
    auto cli = Parser("app", "an example app");

    cli.AddArgument("arg", "a positional argument");
    cli.AddOption("-o", "--opt", "an optional argument");
    cli.AddSubcommand("cmd", "a subcommand");

    ::testing::internal::CaptureStdout();
    cli.Help();
    auto help = ::testing::internal::GetCapturedStdout();

    ASSERT_TRUE(help.contains("app <arg> [options] [command]\n\n") &&
                help.contains("arguments:\n\n") && help.contains("options:\n\n") &&
                help.contains("commands:\n\n") &&
                help.contains("  arg    a positional argument\n\n") &&
                help.contains("  -o, --opt    an optional argument\n\n") &&
                help.contains("  cmd    a subcommand\n\n"));
}
