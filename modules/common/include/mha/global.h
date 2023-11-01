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
            // SPDLOG_ERROR("could not initialize curl! error_code: {}", res);
        }
    }

    ~GlobalInitializer() { curl_global_cleanup(); }
};

#endif // SMARTMHA_GLOBAL_H

MHA_NAMESPACE_END