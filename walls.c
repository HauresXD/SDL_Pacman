#include "walls.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define DEF_SIZE 50
#define GRID_SIZE 50

void drawWall(SDL_Renderer *renderer, int width, int height, int id, SDL_Rect *walls) {

    SDL_SetRenderDrawColor(renderer, 0, 0, 150, 255);

    for(int w = 0; w < WINDOW_WIDTH; w += GRID_SIZE) {

        for(int h = 0; h < WINDOW_HEIGHT; h += GRID_SIZE) {

            if(w / GRID_SIZE == width && h / GRID_SIZE == height) {

                SDL_Rect rect = {.x = w, .y = h, .w = GRID_SIZE, .h = GRID_SIZE};
                SDL_RenderFillRect(renderer, &rect);
                walls[id] = rect;
            }
        }
    }
}
