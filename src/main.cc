#include <iostream>
#include <set>
#include "command_line.hpp"
#include "cxxopts.hpp"
#include "loguru.hpp"

static auto GetDate() -> std::string {
    auto now = std::chrono::system_clock::now();
    auto tt = std::chrono::system_clock::to_time_t(now);
    auto tm = localtime(&tt);
    char buff[12];
    std::sprintf(
            buff, "%d-%02d-%02d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday);

    return buff;
}

int main(int argc, char *argv[]) {
    loguru::init(argc, argv);
    loguru::add_file(
            (std::string("/tmp/smartmha/") + GetDate() + ".log").c_str(),
            loguru::Append,
            loguru::Verbosity_WARNING);

    cxxopts::Options options("smartmha", "The MySQL Cluster Autopilot Management with GTID and Raft");


    options.add_options("MemberFlags")(
            "name",
            "Human-readable name for this member.",
            cxxopts::value<std::string>()->default_value("default")
    )(
            "heartbeat-interval",
            "Time (in milliseconds) of a heartbeat interval.",
            cxxopts::value<int>()->default_value("1000")

    )(
            "election-timeout",
            "Time (in milliseconds) for an election to timeout.",
            cxxopts::value<int>()->default_value("3000")

    )(
            "port",
            "Port listen on.",
            cxxopts::value<int>()->default_value("2380"));

    options.add_options("ClusteringFlags")(
            "initial-advertise-url",
            "This member’s peer URL to advertise to the rest of the cluster. This address is used for communicating around the cluster. It must be routable to all cluster members.",
            cxxopts::value<std::string>()->default_value("http://localhost:2380")
    )(
            "initial-cluster",
            "Initial cluster configuration for bootstrapping.",
            cxxopts::value<std::string>()->default_value("default=http://localhost:2380")
    )(
            "pre-leader-start-command",
            "The shell command when pre leader start.",
            cxxopts::value<std::string>()->default_value("")
    )(
            "post-leader-start-command",
            "The shell command when post leader started.",
            cxxopts::value<std::string>()->default_value("default=http://localhost:2380")
    );

    auto parseResult = options.parse(argc, argv);

    if (parseResult.count("help")) {
        std::cout << options.help() << std::endl;
        return 0;
    }

    std::set<std::string> subcommand_flags;
    subcommand_flags.insert("--version");
    subcommand_flags.insert("-v");
    subcommand_flags.insert("--help");
    subcommand_flags.insert("-h");

    if (argc == 1 || argv[1][0] == '-' && subcommand_flags.count(argv[1]) == 0) {
        return main_smartmha_porcelain(argc, argv);
    } else {
        std::string subcommand = argv[1];
        if (subcommand == "create") {
            return main_smartmha_create(argc, argv);
        } else if (subcommand == "--version" || subcommand == "-v") {
            print_version_message();
            return 0;
        } else if (subcommand == "help" || subcommand == "--help" || subcommand == "-h") {
            if (argc == 2) {
                help_smartmha_porcelain();
                return 0;
            } else if (argc == 3) {
                std::string subcommand2 = argv[2];
                if (subcommand2 == "create") {
                    help_smartmha_create();
                    return 0;
                }
            }
        }
    }

    return 0;
}
