#include "points.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define DEF_SIZE 50
#define GRID_SIZE 50

void placeSpecialPoints(SDL_Renderer *renderer, int x, int y, int id, SDL_Rect *sPointsD, Special *sPoints) {

    SDL_SetRenderDrawColor(renderer, 210, 124, 15, 255);

    for(int w = 0; w < WINDOW_WIDTH; w += GRID_SIZE) {

        for(int h = 0; h < WINDOW_HEIGHT; h += GRID_SIZE) {

            if(w / GRID_SIZE == x && h / GRID_SIZE == y) {

                if(sPoints[id].skip != 1) {

                    SDL_Rect rect = {.x = w+20, .y = h+20, .w = 10, .h = 10};
                    SDL_RenderFillRect(renderer, &rect);
                    sPointsD[id] = rect;
                }
            }
        }
    }
}

void placePoints(SDL_Renderer *renderer, int x, int y, int id, SDL_Rect *pointsD, Point *points) {

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for(int w = 0; w < WINDOW_WIDTH; w += GRID_SIZE) {

        for(int h = 0; h < WINDOW_HEIGHT; h += GRID_SIZE) {

            if(w / GRID_SIZE == x && h / GRID_SIZE == y) {

                if(points[id].skip != 1) {

                    SDL_Rect rect = {.x = w+22, .y = h+22, .w = 5, .h = 5};
                    SDL_RenderFillRect(renderer, &rect);
                    pointsD[id] = rect;
                }
            }
        }
    }
}

void delPoint(int id, Point *points, int numOfWalls) {

    for(int i = 0; i < numOfWalls; i++) {

        if(points[i].id == id) {

            points[i].skip = 1;
            break;
        }
    }
}

void delSpecialPoints(int id, Special *sPoints) {

    int num = 4;
    for(int i = 0; i < num; i++) {

        if (sPoints[i].id == id) {

            sPoints[i].skip = 1;
            break;
        }
    }
}
