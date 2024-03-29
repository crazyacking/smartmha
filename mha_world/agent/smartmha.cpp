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

#include "mha/config.h"
#include "mha/http_client.h"
#include "mha/log.h"
#include "mha/raft.h"
#include "mha/utils.h"
#include <iostream>

using namespace MHA_NAMESPACE;
using namespace std;

int main(int argc, char *argv[]) {
    log::init();
    auto options    = Option::init();
    const auto args = options.parse(argc, argv);

    if (args.count("help")) {
        std::cout << options.help() << std::endl;
        std::exit(EXIT_SUCCESS);
    }

    configuration config(args);
    MHA_LOG_INFO("member name: {}", config.member.name);

    const auto client_ = std::make_unique<HttpClient>("https://www.cnblogs.com/");

    int status{-1};
    std::string response_body = client_->get("", {}, &status);
    MHA_LOG_INFO("http_status={} response_body={}", status, response_body);
    MHA_LOG_INFO("----------- smartmha end -----------");
    return 0;
}
