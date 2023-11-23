#include "config.h"
#include "mysql.h"
#include "mysqld.h"
#include "raft.h"
#include "xbase/xlog.h"
#include "xbase/xrpc.h"
#include <chrono>
#include <stdexcept>
#include <string>

class RPCS {
  public:
    std::shared_ptr<NodeRPC> NodeRPC;
    std::shared_ptr<ServerRPC> ServerRPC;
    std::shared_ptr<UserRPC> UserRPC;
    std::shared_ptr<raft::HARPC> HARPC;
    std::shared_ptr<raft::RaftRPC> RaftRPC;
    std::shared_ptr<mysqld::MysqldRPC> MysqldRPC;
    std::shared_ptr<mysqld::BackupRPC> BackupRPC;
    std::shared_ptr<mysql::MysqlRPC> MysqlRPC;
};

class Server {
  public:
    xlog::Log log;
    mysqld::Mysqld mysqld;
    mysql::Mysql mysql;
    raft::Raft raft;
    config::Config conf;
    xrpc::Service rpc;
    RPCS rpcs;
    std::chrono::system_clock::time_point begin;

    Server(config::Config conf, xlog::Log &log, raft::State initState)
        : log(log)
        , conf(conf) {
        // Implementation might change depending on constructor definition
        mysqld = mysqld::NewMysqld(conf.Backup, log);
        mysql  = mysql::NewMysql(conf.Mysql, conf.Raft.ElectionTimeout, log);
        raft   = raft::NewRaft(conf.Server.Endpoint, conf.Raft, conf.Mysql.SemiSyncTimeoutForTwoNodes, log, s.mysql,
                               initState);
        try {
            rpc = xrpc::NewService(xrpc::Log(log), xrpc::ConnectionStr(conf.Server.Endpoint));
        } catch (const std::exception &e) { log.error("server.rpc.NewService.error:{}", err); }
    }

    void Init() {
        setupMysqld();
        setupMysql();
        setupRPC();
    }

    // Rest of methods go here
};