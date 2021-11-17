cmake_minimum_required(VERSION 3.4)

SET(CMAKE_TOOLCHAIN_FILE "emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake")

project(ray_wasm)

option(OUT_HTML "Output to HTML" OFF)
option(WASM "Compile to WASM" ON)

set(CMAKE_C_STANDARD 11)

# Avoid building the raylib examples
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
set(PLATFORM       Web CACHE BOOL "" FORCE)
add_subdirectory("raylib")

file(GLOB_RECURSE CPP_SOURCES "src/*.cpp")
file(GLOB_RECURSE C_SOURCES "src/*.c")

add_executable(ray_wasm ${CPP_SOURCES} ${C_SOURCES})

target_link_libraries(ray_wasm "raylib")

if(OUT_HTML)
    message(STATUS "Exporting with HTML")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
	set_target_properties(ray_wasm PROPERTIES LINK_FLAGS "-s WASM=1 -s EXPORTED_FUNCTIONS='[_main]'")
endif(OUT_HTML)
