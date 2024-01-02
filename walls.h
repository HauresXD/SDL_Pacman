#ifndef WALLS_H_
#define WALLS_H_

    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
    #include <stdbool.h>
    #include <assert.h>
    #include <time.h>

    #include "structs.h"

    void drawWall(SDL_Renderer *renderer, int width, int height, int id, SDL_Rect *walls);

#endif