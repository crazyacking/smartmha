#include "config_yaml.h"

namespace YAML {

template <typename T>
void convert_(const Node &node, const std::string &key, T &t) {
    if (!node.IsDefined() || node.IsNull() || !node[key].IsDefined() || node[key].IsNull())
        return;

    if ((typeid(T) == typeid(std::string) || typeid(T) == typeid(int) || typeid(T) == typeid(bool)) &&
        !node[key].IsScalar())
        return;

    t = node[key].as<T>();
}

Node encode(const Config &c) {
    Node node; // todo
    return node;
}

bool convert<Config>::decode(const Node &node, Config &c) {
    if (!node.IsMap() || node.size() == 0) {
        return false;
    }

    // server
    convert_(node["server"], "name", c.server.name);
    convert_(node["server"], "port", c.server.port);

    // raft
    convert_(node["raft"], "initial-advertise-url", c.raft.initial_advertise_url);
    convert_(node["raft"], "initial-cluster", c.raft.initial_cluster);
    convert_(node["raft"], "initial-cluster-state", c.raft.initial_cluster_state);
    convert_(node["raft"], "initial-cluster-token", c.raft.initial_cluster_token);
    convert_(node["raft"], "leader-start-command", c.raft.leader_start_command);
    convert_(node["raft"], "leader-stop-command", c.raft.leader_stop_command);
    convert_(node["raft"], "heartbeat-interval", c.raft.heartbeat_interval);
    convert_(node["raft"], "heartbeat-timeout", c.raft.heartbeat_timeout);
    convert_(node["raft"], "election-timeout", c.raft.election_timeout);

    // mysql
    convert_(node["mysql"], "port", c.mysql.port);
    convert_(node["mysql"], "admin-user", c.mysql.admin_user);
    convert_(node["mysql"], "admin-password", c.mysql.admin_password);
    convert_(node["mysql"], "repl-user", c.mysql.repl_user);
    convert_(node["mysql"], "repl-password", c.mysql.repl_password);
    convert_(node["mysql"], "base-dir", c.mysql.base_dir);
    convert_(node["mysql"], "conf-file", c.mysql.conf_file);
    convert_(node["mysql"], "ping-timeout", c.mysql.ping_timeout);
    convert_(node["mysql"], "shutdown-on-exit", c.mysql.shutdown_on_exit);
    convert_(node["mysql"], "diagnose-statements", c.mysql.diagnose_statements);
    convert_(node["mysql"], "heartbeat-table", c.mysql.heartbeat_table);
    convert_(node["mysql"], "cluster-view-table", c.mysql.cluster_view_table);
    convert_(node["mysql"], "heartbeat-statements", c.mysql.heartbeat_statements);
    convert_(node["mysql"], "base-options", c.mysql.base_options);
    convert_(node["mysql"], "extra-options", c.mysql.extra_options);

    return true;
}

} // namespace YAML