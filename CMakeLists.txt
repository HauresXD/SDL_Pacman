cmake_minimum_required(VERSION 3.4)

project(main)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")

find_package(SDL2)

add_executable(main main.c sdl_playground.c ghosts.c points.c walls.c files.c screens.c)

target_include_directories(main PRIVATE ${SDL2_INCLUDE_DIRS})

target_link_libraries(main -lSDL2 -lSDL2_image -lSDL2_ttf m)

