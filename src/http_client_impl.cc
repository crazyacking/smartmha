//
// Created by Dylan Jiang on 2022/6/30.
//

#include "http_client_impl.hpp"
#include <curl/curl.h>

HttpClientImpl::HttpClientImpl() = default;

HttpClientImpl::HttpClientImpl(const std::string &host_port, bool verbose) : verbose_(verbose) {
    set_host(host_port);
    host_port_ = host_port;
    curl_global_init(CURL_GLOBAL_ALL);
}

HttpClientImpl::~HttpClientImpl() { curl_global_cleanup(); }

static void setup_status_code(int *output, CURL *curl) {
    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    if (output) {
        *output = (int) http_code;
    }
}

static void setup_curl_headers(CURL *curl, const std::vector<std::string> &headers) {
    if (headers.empty()) {
        return;
    }
    struct curl_slist *chunk = nullptr;
    for (const auto &pair: headers) {
        chunk = curl_slist_append(chunk, pair.c_str());
    }
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
}

static size_t curl_write_callback_func(void *contents, size_t size, size_t nmemb, std::string *s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char *) contents, newLength);
    } catch (std::bad_alloc &e) {
        // handle memory problem
        return 0;
    }
    return newLength;
}

static void setup_curl_common(CURL *curl, const std::string &url,
                              const std::vector<std::string> &headers, bool verbose,
                              std::string *resp_body = nullptr) {
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    setup_curl_headers(curl, headers);
    if (verbose) {
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); // 允许curl打印出冗长的操作信息
    }
    if (resp_body) {
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write_callback_func);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, resp_body);
    }
}

std::string HttpClientImpl::get_via_curl(const std::string &path,
                                         const std::vector<std::string> &headers,
                                         int *status) const {
    CURL *curl = curl_easy_init();
    if (!curl) return "";

    std::string resp_body;
    setup_curl_common(curl, url(path), headers, verbose_, &resp_body);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, connect_timeout_sec_);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout_sec_);
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        logger->error("error: {}", curl_easy_strerror(res));
        return "";
    }
    setup_status_code(status, curl);
    curl_easy_cleanup(curl);
    return resp_body;
}

std::string HttpClientImpl::post_via_curl(const std::string &path,
                                          const std::string &body,
                                          const std::vector<std::string> &headers,
                                          int *status) const {
    CURL *curl = curl_easy_init();
    if (!curl) {
        return "";
    }
    std::string resp_body;
    setup_curl_common(curl, url(path), headers, verbose_, &resp_body);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, connect_timeout_sec_);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout_sec_);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.data());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, body.size());
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        logger->error("error: {}", curl_easy_strerror(res));
        return "";
    }
    setup_status_code(status, curl);
    curl_easy_cleanup(curl);
    return resp_body;
}

