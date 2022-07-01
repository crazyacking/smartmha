//
// Created by Dylan Jiang on 2022/6/30.
//

#ifndef SMARTMHA_HTTP_CLIENT_IMPL_H
#define SMARTMHA_HTTP_CLIENT_IMPL_H

#include "http_client.hpp"
#include "spdlog/logger.h"
#include "logging.hpp"

class HttpClientImpl : public HttpClient {
public:
    HttpClientImpl();

    explicit HttpClientImpl(const std::string &host_port, bool verbose = false);

    virtual ~HttpClientImpl();

    void set_timeout(const int &sec) override { timeout_sec_ = sec; }

    void set_connect_timeout(const int &sec) override { connect_timeout_sec_ = sec; };

    void set_host(const std::string &host_port) override { host_port_ = host_port; };

    inline const std::string get_host() const { return host_port_; }

    inline std::string get(const std::string &path,
                           const std::vector<std::string> &headers = {},
                           int *status = nullptr) const override {
        return get_via_curl(path, headers, status);
    }

    inline std::string post(const std::string &path,
                            const std::string &body,
                            const std::vector<std::string> &headers = {},
                            int *status = nullptr) const override {
        return post_via_curl(path, body, headers, status);
    }

private:
    std::string host_port_ = "";
    int timeout_sec_ = 60;
    int connect_timeout_sec_ = 120;
    const bool verbose_ = false;

    std::shared_ptr<spdlog::logger> logger = logging::getAppLogger();

    inline std::string url(const std::string &path) const {
        return path.empty() ? host_port_ : host_port_ + (path[0] == '/' ? "" : "/") + path;

    }

    std::string get_via_curl(const std::string &path,
                             const std::vector<std::string> &headers = {},
                             int *status = nullptr) const;

    std::string post_via_curl(const std::string &path,
                              const std::string &body,
                              const std::vector<std::string> &headers,
                              int *status = nullptr) const;
};

#endif //SMARTMHA_HTTP_CLIENT_IMPL_H
