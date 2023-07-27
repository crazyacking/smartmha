#pragma once

#include "config.h"
#include "yaml-cpp/yaml.h"

namespace YAML {

template <>
struct convert<Config> {
    static Node encode(const Config &c);
    static bool decode(const Node &node, Config &c);
};

} // namespace YAML