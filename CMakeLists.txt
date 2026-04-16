cmake_minimum_required(VERSION 3.20)
project(chess_v1 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(chess_v1
    src/main.c
    src/board.c 
    src/utils.c 
    src/piece.c
    src/render.c
)

target_include_directories(chess_v1 PRIVATE src)

if (MSVC AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(chess_v1 PRIVATE /fsanitize=address)
endif()

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        5.5
)
FetchContent_MakeAvailable(raylib)

target_link_libraries(chess_v1 PRIVATE raylib)