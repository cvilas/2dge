#include "game/game.hpp"

#include <thread>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>

#include "logger/logger.hpp"

namespace game {

struct Game::Impl {
  static constexpr auto WINDOW_WIDTH = 800;
  static constexpr auto WINDOW_HEIGHT = 600;
  static constexpr auto PLAYER_INIT_POSITION = glm::vec2{ 10.0, 20.0 };
  static constexpr auto PLAYER_INIT_VELOCITY = glm::vec2{ 10., 5. };
  static constexpr auto FRAME_TIME = std::chrono::duration<double>(1. / 60);

  glm::vec2 player_position{ PLAYER_INIT_POSITION };
  glm::vec2 player_velocity{ PLAYER_INIT_VELOCITY };
  std::chrono::high_resolution_clock::time_point last_frame_ts{};
  SDL_Window* window{ nullptr };
  SDL_Renderer* renderer{ nullptr };
  bool is_running{ true };
};

//-------------------------------------------------------------------------------------------------
Game::Game() : impl_(std::make_unique<Game::Impl>()) {
  if (0 != SDL_Init(SDL_INIT_EVERYTHING)) {
    throw "SDL_Init failed";
  }

  auto display_mode = SDL_DisplayMode();
  SDL_GetCurrentDisplayMode(0, &display_mode);
  impl_->window = SDL_CreateWindow("2dge",                                               //
                                   SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,       //
                                   Game::Impl::WINDOW_WIDTH, Game::Impl::WINDOW_HEIGHT,  //
                                   SDL_WINDOW_BORDERLESS);
  if (impl_->window == nullptr) {
    throw "SDL_CreateWindow failed";
  }

  static constexpr auto DEFAULT_WINDOW = -1;
  impl_->renderer = SDL_CreateRenderer(impl_->window, DEFAULT_WINDOW,
                                       SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (impl_->renderer == nullptr) {
    throw "SDL_CreateRenderer failed";
  }

  // fake fullscreen (blow up game window size to full screen)
  if (0 != SDL_SetWindowFullscreen(impl_->window, SDL_WINDOW_FULLSCREEN)) {
    throw "SDL_SetWindowFullscreen Initialised";
  }
}

//-------------------------------------------------------------------------------------------------
Game::~Game() {
  if (impl_->renderer != nullptr) {
    SDL_DestroyRenderer(impl_->renderer);
  }
  if (impl_->window == nullptr) {
    SDL_DestroyWindow(impl_->window);
  }
  SDL_Quit();
  impl_.reset();
}

//-------------------------------------------------------------------------------------------------
void Game::setup() {
  impl_->last_frame_ts = std::chrono::high_resolution_clock::now();
}

//-------------------------------------------------------------------------------------------------
void Game::run() {
  setup();
  while (impl_->is_running) {
    processInputs();
    update(std::chrono::high_resolution_clock::now());
    render();
  }
}

//-------------------------------------------------------------------------------------------------
void Game::processInputs() {
  auto event = SDL_Event();
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        impl_->is_running = false;
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          impl_->is_running = false;
        }
        break;
    };
  }
}

//-------------------------------------------------------------------------------------------------
void Game::update(std::chrono::high_resolution_clock::time_point tp) {
  static auto last_tp = tp;
  const auto dt = std::chrono::duration_cast<std::chrono::duration<float>>(tp - last_tp).count();
  last_tp = tp;

  // NOLINTBEGIN(cppcoreguidelines-pro-type-union-access)
  impl_->player_position.x += impl_->player_velocity.x * dt;
  impl_->player_position.y += impl_->player_velocity.y * dt;
  // NOLINTEND(cppcoreguidelines-pro-type-union-access)

  // sleep until next update time
  const auto now = std::chrono::high_resolution_clock::now();
  const auto wakeup_tp = (now - tp > Game::Impl::FRAME_TIME) ? now : (tp + Game::Impl::FRAME_TIME);
  std::this_thread::sleep_until(wakeup_tp);
}

//-------------------------------------------------------------------------------------------------
void Game::render() {
  static constexpr std::uint8_t BK_R = 21;
  static constexpr std::uint8_t BK_G = 21;
  static constexpr std::uint8_t BK_B = 21;
  static constexpr std::uint8_t BK_A = 255;
  SDL_SetRenderDrawColor(impl_->renderer, BK_R, BK_G, BK_B, BK_A);
  SDL_RenderClear(impl_->renderer);

  // Draw a PNG texture
  SDL_Surface* surface = IMG_Load("../assets/images/tank-tiger-right.png");
  SDL_Texture* texture = SDL_CreateTextureFromSurface(impl_->renderer, surface);
  SDL_FreeSurface(surface);

  // NOLINTBEGIN(cppcoreguidelines-pro-type-union-access)
  SDL_Rect dst_rect = { static_cast<int>(impl_->player_position.x),
                        static_cast<int>(impl_->player_position.y), 32, 32 };
  // NOLINTEND(cppcoreguidelines-pro-type-union-access)

  SDL_RenderCopy(impl_->renderer, texture, nullptr /*src_rect*/, &dst_rect);
  SDL_DestroyTexture(texture);

  SDL_RenderPresent(impl_->renderer);
}

}  // namespace game