#include <cstdlib>
#include <string>
#include <stdexcept>
#include "safe_getenv.h"

std::string safe_getenv(const char* name) {
    const char* value = std::getenv(name);
    if (!value) {
        throw std::runtime_error("Environment variable " + std::string(name) + " not set!");
    }
    return value;
  }
