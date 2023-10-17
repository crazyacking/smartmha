#pragma once

#ifndef SMARTMHA_RAFT_H
#define SMARTMHA_RAFT_H

#include <cstdint>

// MHA_NAMESPACE_BEGIN

enum State {
    STATE_LEADER        = 1,
    STATE_TRANSFERRING  = 2,
    STATE_CANDIDATE     = 3,
    STATE_FOLLOWER      = 4,
    STATE_ERROR         = 5,
    STATE_UNINITIALIZED = 6,
    STATE_SHUTTING      = 7,
    STATE_SHUTDOWN      = 8,
    STATE_END,
};

// Status of a peer
struct PeerStatus {
    PeerStatus()
        : valid(false)
        , installing_snapshot(false)
        , blocking(false)
        , next_index(0)
        , last_rpc_send_timestamp(0)
        , flying_append_entries_size(0)
        , readonly_index(0)
        , consecutive_error_times(0) {}

    bool valid;
    bool installing_snapshot;
    bool blocking;
    int64_t next_index;
    int64_t last_rpc_send_timestamp;
    int64_t flying_append_entries_size;
    int64_t readonly_index;
    int consecutive_error_times;
};

#endif // SMARTMHA_RAFT_H

// MHA_NAMESPACE_END