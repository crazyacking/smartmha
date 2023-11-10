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

#pragma once

#include "mha/base.h"
#include <atomic>
#include <cassert>
#include <chrono>
#include <iomanip>
#include <mutex>
#include <shared_mutex>
#include <string>

MHA_NAMESPACE_BEGIN

typedef std::shared_timed_mutex mha_lock_mutex;
typedef std::unique_lock<mha_lock_mutex> mha_write_lock;
typedef std::shared_lock<mha_lock_mutex> mha_read_lock;

class Spinlock {
  public:
    Spinlock() = default;
    Spinlock(const Spinlock &) { busy_.store(false); };

    ~Spinlock() { assert(!busy_.load(std::memory_order_relaxed)); }

    void lock() noexcept {
        while (busy_.exchange(true, std::memory_order_acquire)) {}
    }

    void unlock() noexcept { busy_.store(false, std::memory_order_release); }

  private:
    std::atomic<bool> busy_ = {false};
};

class MHARWLock final {
  public:
    MHARWLock()
        : read_counter_(0) {}
    MHARWLock(const MHARWLock &other)
        : read_counter_(0) {}

    void rLock() {
        l_mutex_.lock();
        if (++read_counter_ == 1) {
            g_mutex_.lock();
        }
        l_mutex_.unlock();
    }

    void rUnlock() {
        l_mutex_.lock();
        if (--read_counter_ == 0) {
            g_mutex_.unlock();
        }
        l_mutex_.unlock();
    }

    void wLock() { g_mutex_.lock(); }

    void wUnlock() { g_mutex_.unlock(); }

  private:
    Spinlock l_mutex_;
    Spinlock g_mutex_;
    int32_t read_counter_;
};

class RLockGuard {
  public:
    explicit RLockGuard(MHARWLock &rwlock)
        : rw_lock_(rwlock) {
        rw_lock_.rLock();
    }
    ~RLockGuard() { rw_lock_.rUnlock(); }

    void unlock() { rw_lock_.rUnlock(); }

  private:
    MHARWLock &rw_lock_;
};

class WLockGuard {
  public:
    explicit WLockGuard(MHARWLock &rwlock)
        : rw_lock_(rwlock) {
        rw_lock_.wLock();
    }
    ~WLockGuard() { rw_lock_.wUnlock(); }

    void unlock() { rw_lock_.wUnlock(); }

  private:
    MHARWLock &rw_lock_;
};

MHA_NAMESPACE_END