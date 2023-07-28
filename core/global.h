//
// Created by Dylan Jiang on 2023/7/28.
//

#ifndef SMARTMHA_GLOBAL_H
#define SMARTMHA_GLOBAL_H

#include "log.h"
#include <curl/curl.h>

MHA_NAMESPACE_BEGIN

class GlobalInitializer {
  public:
    GlobalInitializer() {
        const auto res = curl_global_init(CURL_GLOBAL_ALL);
        if (res != CURLE_OK) {
            SPDLOG_ERROR("could not initialize curl! error_code: {}", res);
        }
    }

    ~GlobalInitializer() { curl_global_cleanup(); }
};

#endif // SMARTMHA_GLOBAL_H

MHA_NAMESPACE_END