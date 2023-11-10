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

#include "mha/utils.h"
#include "gtest/gtest.h"
#include <iostream>
#include <mha/log.h>

using namespace MHA_NAMESPACE;

TEST(mha_utils_test, test_get_date) {
    const auto &date = GetDate();
    MHA_LOG_INFO(date)
    EXPECT_EQ(date.size(), 10);
}
