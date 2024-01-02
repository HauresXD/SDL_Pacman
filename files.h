#ifndef FILES_H_
#define FILES_H_

    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
    #include <stdbool.h>
    #include <assert.h>
    #include <time.h>

    #include "structs.h"

    int readFile(SDL_Renderer *ren, Wall *walls, Pacman *pman, GhostSpawn *gSpawn, Special *sPoints, Point *points);
    int readBestScore();
    void writeBestScore(int new);

#endif