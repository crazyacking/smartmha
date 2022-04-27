#include "yaml-cpp/yaml.h"
#include "config.hpp"

namespace YAML {

template<>
struct convert<Config> {
    static Node encode(const Config &c);
    static bool decode(const Node &node, Config &c);
};

}