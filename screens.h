#ifndef SCREENS_H_
#define SCREENS_H_

    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
    #include <stdbool.h>
    #include <assert.h>
    #include <time.h>

    void winningScreen(SDL_Renderer *renderer);
    void losingScreen(SDL_Renderer *renderer, int points);

#endif