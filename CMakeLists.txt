cmake_minimum_required(VERSION 3.4)

SET(CMAKE_TOOLCHAIN_FILE "emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake")

project(RayWasm)
option(OUT_HTML "Output to HTML" OFF)
option(WASM "Compile to WASM" ON)


file(GLOB_RECURSE CPP_SOURCES "src/*.cpp")
file(GLOB_RECURSE C_SOURCES "src/*.c")

add_executable(RayWasm ${CPP_SOURCES} ${C_SOURCES})

if(OUT_HTML)
    message(STATUS "Exporting with HTML")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
	set_target_properties(RayWasm PROPERTIES LINK_FLAGS "-s WASM=1 -s EXPORTED_FUNCTIONS='[_main]'")
endif(OUT_HTML)
