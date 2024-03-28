# 2dge - Pikuma 2D Game Engine Course

## Introduction

This repo contains my project files for Pikuma's [C++ Game Engine Programming Course](https://pikuma.com/courses/cpp-2d-game-engine-development). Based on code templates provided in the course (i.e. this is not representative of how I normally develop software)

## Setup

- Install system dependencies

```bash
sudo apt install build-essential libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev liblua5.3-dev libglm-dev cmake 
```

- Install compiler that supports C++23

```bash
wget https://apt.llvm.org/llvm.sh
export CLANG_VERSION=18 # Replace with latest version number
chmod +x llvm.sh
sudo ./llvm.sh $CLANG_VERSION
sudo apt install clang-$CLANG_VERSION clang-tidy-$CLANG_VERSION clang-format-$CLANG_VERSION \
llvm-$CLANG_VERSION-dev libc++-$CLANG_VERSION-dev libomp-$CLANG_VERSION-dev \
libc++abi-$CLANG_VERSION-dev libunwind-$CLANG_VERSION-dev
sudo update-alternatives --remove-all clang
sudo update-alternatives --install /usr/bin/clang clang \
/usr/bin/clang-$CLANG_VERSION $CLANG_VERSION \
--slave /usr/bin/clang++ clang++ /usr/bin/clang++-$CLANG_VERSION \
--slave /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-$CLANG_VERSION \
--slave /usr/bin/clang-format clang-format /usr/bin/clang-format-$CLANG_VERSION
```

- Build

```bash
git clone git@github.com:cvilas/2dge.git
cd 2dge
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=$PWD/../toolchain_clang.cmake
```

## TODO
