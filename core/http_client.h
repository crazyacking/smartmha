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
