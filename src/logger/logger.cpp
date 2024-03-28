#include "logger.hpp"

#include <chrono>
#include <print>

namespace game {

[[maybe_unused]] static constexpr auto RESET = "\033[0m";
[[maybe_unused]] static constexpr auto BLACK = "\033[30m";
[[maybe_unused]] static constexpr auto RED = "\033[31m";
[[maybe_unused]] static constexpr auto GREEN = "\033[32m";
[[maybe_unused]] static constexpr auto YELLOW = "\033[33m";
[[maybe_unused]] static constexpr auto BLUE = "\033[34m";
[[maybe_unused]] static constexpr auto WHITE = "\033[37m";

void Logger::log(const std::string& msg) {
  std::println(stderr, "LOG [{}] {}", std::chrono::system_clock::now(), msg);
}

void Logger::err(const std::string& msg) {
  std::println(stderr, "{}ERR [{}] {}{}", RED, std::chrono::system_clock::now(), msg, RESET);
}
}  // namespace game