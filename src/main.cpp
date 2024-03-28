#include <cstdlib>
#include <print>

#include "game/game.hpp"

int main(int argc, const char* argv[]) {
  try {
    (void)argc;
    (void)argv;
    auto game = game::Game();
    game.run();
    return EXIT_SUCCESS;
  } catch (const std::string& str) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
    std::ignore = fprintf(stderr, "%s\n", str.c_str());
    return EXIT_FAILURE;
  } catch (const std::exception& ex) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
    std::ignore = fprintf(stderr, "%s\n", ex.what());
    return EXIT_FAILURE;
  } catch (...) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
    std::ignore = fprintf(stderr, "Unknown exception\n");
    return EXIT_FAILURE;
  }
}
