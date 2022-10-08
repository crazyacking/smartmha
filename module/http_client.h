//
// Created by Dylan Jiang on 2022/6/30.
//

#ifndef SMARTMHA_HTTP_CLIENT_H
#define SMARTMHA_HTTP_CLIENT_H

#include <string>
#include <vector>

class HttpClient {
public:
    virtual void set_host(const std::string &host_port) = 0;

    virtual std::string get(const std::string &path,
                            const std::vector<std::string> &headers = {},
                            int *status = nullptr) const = 0;

    virtual std::string post(const std::string &path,
                             const std::string &body,
                             const std::vector<std::string> &headers = {},
                             int *status = nullptr) const = 0;

    virtual void set_timeout(const int &sec) = 0;

    virtual void set_connect_timeout(const int &sec) = 0;

    virtual ~HttpClient() {}
};

#endif //SMARTMHA_HTTP_CLIENT_H
