cmake_minimum_required(VERSION 3.27)
project(2dge LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
include(cmake/linter.cmake)
add_compile_options(-Wall -Wextra -Wpedantic -Werror
                    -Wno-unknown-warning-option)

set(SOURCES
    ./src/ecs/ecs.hpp
    ./src/ecs/ecs.cpp
    ./src/components/transform.h
    ./src/systems/movement.h
    ./src/game/game.hpp
    ./src/game/game.cpp
    ./src/logger/logger.hpp
    ./src/logger/logger.cpp
    ./src/main.cpp)

add_executable(game ${SOURCES})
add_clang_format(game)
target_link_libraries(game PRIVATE SDL2 SDL2_image SDL2_ttf lua5.4)
target_include_directories(game
  PRIVATE ${CMAKE_SOURCE_DIR}/libs/
          ${CMAKE_SOURCE_DIR}/src/
          /usr/include/lua5.4
          /opt/homebrew/Cellar/lua@5.3/5.4.6/include
          /opt/homebrew/Cellar/lua@5.3/5.4.6/include/lua5.3
          /opt/homebrew/include)
target_link_directories(game PRIVATE /opt/homebrew/Cellar/lua@5.4/5.4.6/lib/
                        /opt/homebrew/lib)
