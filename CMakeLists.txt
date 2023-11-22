cmake_minimum_required(VERSION 3.18)

project(sdlapp)

find_package(SDL2 REQUIRED)

add_executable(main main.c)
target_link_libraries(main SDL2 SDL2_image SDL2_ttf)