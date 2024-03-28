#pragma once
#include <string>

namespace game {
class Logger {
public:
  static void log(const std::string& msg);
  static void err(const std::string& msg);
};
}  // namespace game