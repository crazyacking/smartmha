#pragma once

#include "yaml-cpp/yaml.h"
#include "config.h"

namespace YAML {

template<>
struct convert<Config> {
    static Node encode(const Config &c);
    static bool decode(const Node &node, Config &c);
};

}