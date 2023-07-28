#pragma once

#include "base.h"
#include <atomic>
#include <chrono>
#include <shared_mutex>
#include <string>

MHA_NAMESPACE_BEGIN

#define MSTR(x) stringify(x) // Stringify a macro
#if defined __clang__
#define COMPILER_STR "CLANG " __clang_version__
#elif defined __GNUC__
#define COMPILER_STR "GCC " MSTR(__GNUC__) "." MSTR(__GNUC_MINOR__) "." MSTR(__GNUC_PATCHLEVEL__)
#elif defined _MSC_VER
#define COMPILER_STR "MSC " MSTR(_MSC_FULL_VER)
#else
#define COMPILER_STR "UNKNOWN COMPILER"
#endif

#define SMARTMHA_VERSION "v1.0.0"

#ifndef NDEBUG
#define SMARTMHA_VERSION_STR                                                                                           \
    "smartmha " SMARTMHA_VERSION " (debug)"                                                                            \
    " (" COMPILER_STR ")"
#else
#define SMARTMHA_VERSION_STR "smartmha " SMARTMHA_VERSION " (" COMPILER_STR ")"
#endif

typedef std::shared_timed_mutex mha_lock_mutex;
typedef std::unique_lock<mha_lock_mutex> mha_write_lock;
typedef std::shared_lock<mha_lock_mutex> mha_read_lock;

static auto GetDate() -> std::string {
    auto now = std::chrono::system_clock::now();
    auto tt  = std::chrono::system_clock::to_time_t(now);
    auto tm  = localtime(&tt);
    char buff[12];
    std::sprintf(buff, "%d-%02d-%02d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday);
    return buff;
}

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