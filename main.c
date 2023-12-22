#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#include "sdl_playground.h"
#include "array.h"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PACMAN_SIZE 50
#define GRID_SIZE 50

typedef struct {
    int id;
    int direction;
    char *color;
    int killable;
} Ghost;

void drawGrid(SDL_Renderer *ren) {

    SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);

    for (int x = 0; x <= WINDOW_WIDTH; x += GRID_SIZE) {

        SDL_RenderDrawLine(ren, x, 0, x, WINDOW_HEIGHT);
    }

    for (int y = 0; y <= WINDOW_HEIGHT; y += GRID_SIZE) {

        SDL_RenderDrawLine(ren, 0, y, WINDOW_WIDTH, y);
    }
}

void makeWall(SDL_Renderer *renderer, int width, int height, int id, SDL_Rect *walls) {

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int w = 0; w < WINDOW_WIDTH; w += GRID_SIZE) {

        for (int h = 0; h < WINDOW_HEIGHT; h += GRID_SIZE) {

            if (w / GRID_SIZE == width && h / GRID_SIZE == height) {

                SDL_Rect rect = {.x = w, .y = h, .w = GRID_SIZE, .h = GRID_SIZE};
                SDL_RenderFillRect(renderer, &rect);
                walls[id] = rect;
            }
        }
    }
}

int main() {

    SDL_Window *win = NULL;
    SDL_Renderer *ren = NULL;
    
    bool initialized = sdl_playground_init(&win, &ren, WINDOW_WIDTH, WINDOW_HEIGHT);

    if(!initialized) {

        sdl_playground_destroy(win, ren);
        return -1;
    }

    int posX = 50;
    int posY = 50;

    int prevPosX = posX;
    int prevPosY = posY;

    int wallCount = 12;

    SDL_Rect *rects = (SDL_Rect *)malloc(wallCount * sizeof(SDL_Rect));

    SDL_Event e;
    bool RUN = true;

    while (RUN) {

        while (SDL_PollEvent(&e)) {

            if (e.type == SDL_QUIT) {

                RUN = false;
            }else if (e.type == SDL_KEYDOWN) {
               
                if(e.key.keysym.sym == SDLK_ESCAPE) {
                    
                    RUN = false;
                }else if(e.key.keysym.sym == SDLK_LEFT) {

                    prevPosX = posX;
                    prevPosY = posY;
                    if(posX != 0) {

                        posX -= 10;
                    }
                }else if(e.key.keysym.sym == SDLK_RIGHT) {

                    prevPosX = posX;
                    prevPosY = posY;
                    if((posX+PACMAN_SIZE) < WINDOW_WIDTH) {

                        posX += 10;
                    }
                }else if(e.key.keysym.sym == SDLK_UP) {

                    prevPosX = posX;
                    prevPosY = posY;
                    if(posY != 0) {

                        posY -= 10;
                    }
                }else if(e.key.keysym.sym == SDLK_DOWN) {

                    prevPosX = posX;
                    prevPosY = posY;
                    if((posY+PACMAN_SIZE) < WINDOW_HEIGHT) {

                        posY += 10;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        // drawGrid(ren);

        // Automatizovat
        makeWall(ren, 0, 0, 0, rects);
        makeWall(ren, 0, 1, 1, rects);
        makeWall(ren, 0, 2, 2, rects);
        makeWall(ren, 0, 3, 3, rects);
        makeWall(ren, 0, 4, 4, rects);
        makeWall(ren, 0, 5, 5, rects);
        makeWall(ren, 0, 6, 6, rects);
        makeWall(ren, 0, 7, 7, rects);
        makeWall(ren, 0, 8, 8, rects);
        makeWall(ren, 0, 9, 9, rects);
        makeWall(ren, 0, 10, 10, rects);
        makeWall(ren, 0, 11, 11, rects);
        makeWall(ren, 0, 12, 12, rects);

        // 'Pacman'
        SDL_SetRenderDrawColor(ren, 255, 255, 0, 255);
        SDL_Rect pacman = {.x = posX, .y = posY, .w = PACMAN_SIZE, .h = PACMAN_SIZE};
        SDL_RenderFillRect(ren, &pacman);

        // if (SDL_HasIntersection(&pacman, &topWall)) {

        //     posX = prevPosX;
        //     posY = prevPosY;
        // }

        for(int i = 0; i < wallCount; i++) {

            if (SDL_HasIntersection(&pacman, &rects[i])) {

                posX = prevPosX;
                posY = prevPosY;
            }
        }

        // SDL_RenderCopyEx(ren, pacman, NULL, &rect, 45, NULL, 0);
        SDL_RenderPresent(ren);
    }

    sdl_playground_destroy(win, ren);

    return 0;
}
