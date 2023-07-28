//
// Created by Dylan Jiang on 2022/6/30.
//

#ifndef SMARTMHA_HTTP_CLIENT_H
#define SMARTMHA_HTTP_CLIENT_H

#include "base.h"
#include "utils.h"
#include <curl/curl.h>
#include <string>
#include <vector>

MHA_NAMESPACE_BEGIN

class HttpClient {
  public:
    explicit HttpClient(const std::string &host_port);
    ~HttpClient() = default;

    void set_host(const std::string &host_port);

    std::string get(const std::string &path, const std::vector<std::string> &headers, int *status) const;

    std::string post(const std::string &path, const std::string &body, const std::vector<std::string> &headers,
                     int *status) const;

    void set_timeout(const int &timeout_sec);

    void set_connect_timeout(const int &sec);

  private:
    std::string host_port_;
    int timeout_sec_         = 60;
    int connect_timeout_sec_ = 120;

    mutable MHARWLock mutex_;

    std::string url(const std::string &path) const;

    std::string get_via_curl(const std::string &path, const std::vector<std::string> &headers, int *status) const;

    std::string post_via_curl(const std::string &path, const std::string &body, const std::vector<std::string> &headers,
                              int *status) const;

    static void setup_curl_common(CURL *curl, const std::string &url, const std::vector<std::string> &headers,
                                  bool verbose, std::string *resp_body = nullptr);
};

#endif // SMARTMHA_HTTP_CLIENT_H

MHA_NAMESPACE_END
