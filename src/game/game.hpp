#pragma once

#include <chrono>
#include <memory>

namespace game {

class Game {
public:
  Game();
  ~Game();
  void run();

private:
  void setup();
  void update(std::chrono::high_resolution_clock::time_point tp);
  void render();
  void processInputs();

  struct Impl;
  std::unique_ptr<Impl> impl_;
};
}  // namespace game