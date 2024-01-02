#ifndef POINTS_H_
#define POINTS_H_

    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
    #include <stdbool.h>
    #include <assert.h>
    #include <time.h>

    #include "structs.h"

    void placeSpecialPoints(SDL_Renderer *renderer, int x, int y, int id, SDL_Rect *sPointsD, Special *sPoints);
    void placePoints(SDL_Renderer *renderer, int x, int y, int id, SDL_Rect *pointsD, Point *points);
    void delPoint(int id, Point *points, int numOfWalls);
    void delSpecialPoints(int id, Special *sPoints);

#endif