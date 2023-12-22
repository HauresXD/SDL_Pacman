cmake_minimum_required(VERSION 3.4)

# Název projektu
project(main)

# Přidání přepínačů překladače
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")

# Vyhledání knihovny SDL
find_package(SDL2)

# Vytvoření programu s názvem `hra`
# Program se bude skládat ze dvou zadaných zdrojových souborů (jednotek překladu)
add_executable(main main.c sdl_playground.c array.c)

# Přidání adresářů s hlavičkovými soubory k programu (obdoba -I)
target_include_directories(main PRIVATE ${SDL2_INCLUDE_DIRS})

# Přilinkování knihoven k programu (obdoba -l)
target_link_libraries(main -lSDL2 -lSDL2_image m)

