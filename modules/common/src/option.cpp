// Copyright (c) 2023 Dylan Jiang(crazyacking). All Rights Reserved
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Authors: Dylan Jiang(crazyacking@gmail.com)

#include "option.h"

MHA_NAMESPACE_BEGIN

cxxopts::Options Option::init() {
    cxxopts::Options options("smartmha", "The MySQL Cluster Autopilot Management with GTID and Raft.");

    // Note that if a configuration file is provided,
    // other command line flags and environment variables will be ignored.
    options.add_options()("h,help", "Display help message.")("c,config-file", "The server configuration file.",
                                                             cxxopts::value<std::string>());

    options.add_options("server")("name", "Human-readable name for this server.",
                                  cxxopts::value<std::string>()->default_value("default"))(
        "port", "Port listen on.", cxxopts::value<int>()->default_value("2380"));

    options.add_options("raft")("initial-advertise-url",
                                "This server’s peer URL to advertise to the rest of the cluster. This address is used "
                                "for communicating around the cluster.",
                                cxxopts::value<std::string>()->default_value("http://localhost:2380"))(
        "initial-cluster", "Initial cluster configuration for bootstrapping.",
        cxxopts::value<std::string>()->default_value("node1=10.0.1.10:2380,node2=10.0.1.11:2380,node3=10.0.1.12:2380"))(
        "pre-leader-start-command", "The shell command when pre leader start.",
        cxxopts::value<std::string>()->default_value(""))(
        "post-leader-start-command", "The shell command when post leader started.",
        cxxopts::value<std::string>()->default_value("default=http://localhost:2380"))(
        "pre-leader-stop-command", "The shell command when pre leader stop.",
        cxxopts::value<std::string>()->default_value(""))("post-leader-stop-command",
                                                          "The shell command when post leader stopped.",
                                                          cxxopts::value<std::string>()->default_value(""))(
        "pre-follower-start-command", "The shell command when pre follower start.",
        cxxopts::value<std::string>()->default_value(""))("post-follower-start-command",
                                                          "The shell command when post follower started.",
                                                          cxxopts::value<std::string>()->default_value(""))(
        "pre-follower-stop-command", "The shell command when pre follower stop.",
        cxxopts::value<std::string>()->default_value(""))("post-follower-stop-command",
                                                          "The shell command when post follower stopped.",
                                                          cxxopts::value<std::string>()->default_value(""))(
        "pre-candidate-start-command", "The shell command when pre candidate start.",
        cxxopts::value<std::string>()->default_value(""))("post-candidate-start-command",
                                                          "The shell command when post candidate started.",
                                                          cxxopts::value<std::string>()->default_value(""))(
        "pre-candidate-stop-command", "The shell command when pre candidate stop.",
        cxxopts::value<std::string>()->default_value(""))("post-candidate-stop-command",
                                                          "The shell command when post candidate stopped.",
                                                          cxxopts::value<std::string>()->default_value(""))(
        "pre-leader-change-command", "The shell command when pre leader change.",
        cxxopts::value<std::string>()->default_value(""))("post-leader-change-command",
                                                          "The shell command when post leader changed.",
                                                          cxxopts::value<std::string>()->default_value(""))(
        "initial-cluster-state", "Initial cluster state ('new' or 'existing').",
        cxxopts::value<std::string>()->default_value(""))(
        "initial-cluster-token", "Initial cluster token for the cluster during bootstrap.",
        cxxopts::value<std::string>()->default_value("smart-mha-cluster"));

    return options;
}

MHA_NAMESPACE_END