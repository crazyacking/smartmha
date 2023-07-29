# smartmha

The MySQL Cluster Autopilot Management with GTID and Raft.

`smartmha` is a MySQL high availability and replication management tool, runs as a service and provides command line access, HTTP API and Web interface. `smartmha` supports:

#### Discovery

`smartmha` actively crawls through your topologies and maps them. It reads basic MySQL info such as replication status and configuration.

It provides you with slick visualization of your topologies, including replication problems, even in the face of failures.

#### Refactoring

`smartmha` understands replication rules. It knows about binlog file:position, GTID, Pseudo GTID, Binlog Servers.

Refactoring replication topologies can be a matter of drag & drop a replica under another master. Moving replicas around is safe: `smartmha` will reject an illegal refactoring attempt.

Fine-grained control is achieved by various command line options.

#### Recovery

`smartmha` uses a holistic approach to detect master and intermediate master failures. Based on information gained from the topology itself, it recognizes a variety of failure scenarios.

Configurable, it may choose to perform automated recovery (or allow the user to choose type of manual recovery). Intermediate master recovery achieved internally to `smartmha`. Master failover supported by pre/post failure hooks.

Recovery process utilizes _smartmha's_ understanding of the topology and of its ability to perform refactoring. It is based on _state_ as opposed to _configuration_: `smartmha` picks the best recovery method by investigating/evaluating the topology at the time of
recovery itself.

# Building

This project supports [CMake](https://cmake.org/) out of the box.

### Build for POSIX

Quick start:

```bash
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build .
```
