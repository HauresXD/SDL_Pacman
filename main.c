#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#include "sdl_playground.h"
#include "array.h"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PACMAN_SIZE 50

typedef struct {
    int id;
    int direction;
    char *color;
    bool killable;
} Ghost;

int main() {

    SDL_Window *win = NULL;
    SDL_Renderer *ren = NULL;
    
    bool initialized = sdl_playground_init(&win, &ren, WINDOW_WIDTH, WINDOW_HEIGHT);

    if(!initialized) {

        sdl_playground_destroy(win, ren);
        return -1;
    }

    int pos_x = 50;
    int pos_y = 50;

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

                    if(pos_x != 0) {

                        pos_x -= 10;
                    }
                }else if(e.key.keysym.sym == SDLK_RIGHT) {

                    if((pos_x+PACMAN_SIZE) < WINDOW_WIDTH) {

                        pos_x += 10;
                    }
                }else if(e.key.keysym.sym == SDLK_UP) {

                    if(pos_y != 0) {

                        pos_y -= 10;
                    }
                }else if(e.key.keysym.sym == SDLK_DOWN) {

                    if((pos_y+PACMAN_SIZE) < WINDOW_HEIGHT) {

                        pos_y += 10;
                    }
                }
            }
            // else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) { // mouse button released
            //     // x: e.button.button.x
            //     // y: e.button.button.y
            // }
            // else if (e.type == SDL_MOUSEMOTION) { // mouse movement
            //     // x: e.motion.x
            //     // y: e.motion.y
            // }
        }

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);

        SDL_Rect rect = {.x = pos_x, .y = pos_y, .w = PACMAN_SIZE, .h = PACMAN_SIZE};

        SDL_RenderFillRect(ren, &rect);
        SDL_RenderPresent(ren);
    }

    sdl_playground_destroy(win, ren);

    return 0;
}
