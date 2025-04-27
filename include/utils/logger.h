#pragma once
#include <string>

namespace utils {
class Logger {
public:
  static void info(const std::string &msg);
  static void warn(const std::string &msg);
  static void err(const std::string &msg);
};
} // namespace utils
