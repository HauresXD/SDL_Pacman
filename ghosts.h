#ifndef GHOSTS_H_
#define GHOSTS_H_

    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
    #include <stdbool.h>
    #include <assert.h>
    #include <time.h>

    #include "structs.h"

    void drawGhosts(SDL_Renderer *renderer, SDL_Rect *ghostsD, Ghost *ghosts, SDL_Texture *ghostsT[]);
    int checkWallCollision(int x, int y, Wall *walls, int numWalls);
    void ghostMovement(Ghost *ghosts, Wall *walls, int numWalls, int pacmanX, int pacmanY, int i, GhostSpawn gSpawn);
    void moveGhosts(Ghost *ghosts, Wall *walls, int numWalls, int pacmanX, int pacmanY, int frame, GhostSpawn gSpawn);


#endif