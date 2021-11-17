#!/usr/bin/env bash

mkdir build

cd build/

CMAKE_TOOLCHAIN_FILE=emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake
../emsdk/upstream/emscripten/emcmake cmake .. -DPLATFORM=Web

intercept-build make
cp compile_commands.json ../compile_commands.json
