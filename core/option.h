#pragma once

#include "base.h"
#include "cxxopts.hpp"

MHA_NAMESPACE_BEGIN

class Option {
  public:
    static cxxopts::Options init();
};

MHA_NAMESPACE_END