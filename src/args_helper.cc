#include "cxxopts.hpp"
#include "args_helper.hpp"

cxxopts::Options InitOptions() {
    cxxopts::Options options("smartmha", "The MySQL Cluster Autopilot Management with GTID and Raft.");

    options.add_options()
            ("h,help", "display help message");

    options.add_options("member")(
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

    options.add_options("clustering")(
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
    )(
            "pre-leader-stop-command",
            "The shell command when pre leader stop.",
            cxxopts::value<std::string>()->default_value("")
    )(
            "post-leader-stop-command",
            "The shell command when post leader stopped.",
            cxxopts::value<std::string>()->default_value("")
    )(
            "pre-follower-start-command",
            "The shell command when pre follower start.",
            cxxopts::value<std::string>()->default_value("")
    )(
            "post-follower-start-command",
            "The shell command when post follower started.",
            cxxopts::value<std::string>()->default_value("")
    )(
            "pre-follower-stop-command",
            "The shell command when pre follower stop.",
            cxxopts::value<std::string>()->default_value("")
    )(
            "post-follower-stop-command",
            "The shell command when post follower stopped.",
            cxxopts::value<std::string>()->default_value("")
    )(
            "pre-candidate-start-command",
            "The shell command when pre candidate start.",
            cxxopts::value<std::string>()->default_value("")
    )(
            "post-candidate-start-command",
            "The shell command when post candidate started.",
            cxxopts::value<std::string>()->default_value("")
    )(
            "pre-candidate-stop-command",
            "The shell command when pre candidate stop.",
            cxxopts::value<std::string>()->default_value("")
    )(
            "post-candidate-stop-command",
            "The shell command when post candidate stopped.",
            cxxopts::value<std::string>()->default_value("")
    )(
            "pre-leader-change-command",
            "The shell command when pre leader change.",
            cxxopts::value<std::string>()->default_value("")
    )(
            "post-leader-change-command",
            "The shell command when post leader changed.",
            cxxopts::value<std::string>()->default_value("")
    )(
            "initial-cluster-state",
            "Initial cluster state ('new' or 'existing'). Set to new for all members present during initial static. If this option is set to existing, polar-ha will attempt to join the existing cluster. If the wrong value is set, polar-ha will attempt to start but fail safely.",
            cxxopts::value<std::string>()->default_value("")
    )(
            "initial-cluster-token",
            "Initial cluster token for the cluster during bootstrap.",
            cxxopts::value<std::string>()->default_value("smart-mha-cluster")
    );

    return options;
}