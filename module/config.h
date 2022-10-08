#pragma once

#include <string>
#include "logging.h"
#include "option.h"
#include "yaml-cpp/yaml.h"

struct Server {
    std::string name = "default";
    int         port = 2380;
};

struct Raft {
    std::string initial_advertise_url = "10.0.1.10:2380";
    std::string initial_cluster       = "node1=10.0.1.10:2380,node2=10.0.1.11:2380,node3=10.0.1.12:2380";
    std::string initial_cluster_state = "new";
    std::string initial_cluster_token = "smartmha-cluster";
    std::string leader_start_command;
    std::string leader_stop_command;
    int         heartbeat_interval    = 1000;
    int         heartbeat_timeout     = 1000;
    int         election_timeout      = 3000;
};

struct Mysql {
    int         port               = 3306;
    std::string admin_user         = "root";
    std::string admin_password;
    std::string repl_user          = "repl";
    std::string repl_password;
    std::string base_dir           = "/usr/sbin/:/usr/bin";
    std::string conf_file          = "/tmp/data";
    int         ping_timeout       = 30; // in milliseconds
    bool        shutdown_on_exit   = false;
    std::string diagnose_statements;
    std::string heartbeat_table    = "mysql.smartmha_heartbeat";
    std::string cluster_view_table = "mysql.smartmha_cluster_view";
    std::string heartbeat_statements;
    std::string base_options; // base options pass to database binary
    std::string extra_options; // extra options pass to database binary
};

struct Config {
    Server server;
    Raft   raft;
    Mysql  mysql;
};


class configuration {
public:
    configuration(cxxopts::ParseResult args);

    Server member;
    Raft   clustering;
    Mysql  mysql;

    std::string config_file;

private:
    YAML::Node config_yaml;

    void parse_yaml();
};