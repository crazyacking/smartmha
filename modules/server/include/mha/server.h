
#pragma once

#include <bitset>
#include <bthread/mutex.h>
#include <unordered_map>

struct Instance {
    std::string address;
    int64_t capacity;
    int64_t used_size;
    std::string resource_tag;
    std::string physical_room;
    std::string logical_room;
    std::string version;
    std::string network_segment;
    std::string network_segment_self_defined;
    int64_t dml_latency        = 0;
    int64_t dml_qps            = 0;
    int64_t raft_total_latency = 0;
    int64_t raft_total_qps     = 0;
    int64_t select_latency     = 0;
    int64_t select_qps         = 0;
    InstanceStateInfo instance_status;

    Instance() {
        instance_status.state     = pb::NORMAL;
        instance_status.timestamp = butil::gettimeofday_us();
    }
    Instance(const pb::InstanceInfo &instance_info)
        : address(instance_info.address())
        , capacity(instance_info.capacity())
        , used_size(instance_info.capacity())
        , resource_tag(instance_info.resource_tag())
        , physical_room(instance_info.physical_room())
        , logical_room(instance_info.logical_room())
        , version(instance_info.version()) {
        if (instance_info.has_used_size()) {
            used_size = instance_info.used_size();
        }
        if (instance_info.has_status() && instance_info.status() == pb::FAULTY) {
            instance_status.state = pb::FAULTY;
        } else {
            instance_status.state = pb::NORMAL;
        }
        instance_status.timestamp = butil::gettimeofday_us();
        if (instance_info.has_network_segment() && !instance_info.network_segment().empty()) {
            network_segment_self_defined = instance_info.network_segment();
            network_segment              = instance_info.network_segment();
        }
    }
};
