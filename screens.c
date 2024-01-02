#include "screens.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define DEF_SIZE 50
#define GRID_SIZE 50
#define FONT_PATH "../arial.ttf"
#define FONT_SIZE 24

void winningScreen(SDL_Renderer *renderer) {

    SDL_Color textColor = {255, 255, 255};
    TTF_Font *font = TTF_OpenFont(FONT_PATH, 50);
    if (!font) {

        fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());
        return;
    }

    char winningText[] = "Vyhrál jsi!";
    SDL_Surface *winningTextSurface = TTF_RenderText_Solid(font, winningText, textColor);
    SDL_Texture *winningTextTexture = SDL_CreateTextureFromSurface(renderer, winningTextSurface);
    SDL_Rect winningTextRect = {.x = WINDOW_WIDTH / 2 - winningTextSurface->w / 2, .y = WINDOW_HEIGHT / 2 - winningTextSurface->h / 2, .w = winningTextSurface->w, .h = winningTextSurface->h};
    SDL_RenderCopy(renderer, winningTextTexture, NULL, &winningTextRect);

    SDL_FreeSurface(winningTextSurface);
    SDL_DestroyTexture(winningTextTexture);
    TTF_CloseFont(font);

    SDL_RenderPresent(renderer);
}

void losingScreen(SDL_Renderer *renderer, int points) {

    SDL_Color textColor = {255, 255, 255};
    TTF_Font *font = TTF_OpenFont(FONT_PATH, 50);
    if (!font) {

        fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());
        return;
    }

    char losingText[40];
    sprintf(losingText, "Prohral jsi! Points: %d", points);
    SDL_Surface *losingTextSurface = TTF_RenderText_Solid(font, losingText, textColor);
    SDL_Texture *losingTextTexture = SDL_CreateTextureFromSurface(renderer, losingTextSurface);
    SDL_Rect losingTextRect = {.x = WINDOW_WIDTH / 2 - losingTextSurface->w / 2, .y = WINDOW_HEIGHT / 2 - losingTextSurface->h / 2, .w = losingTextSurface->w, .h = losingTextSurface->h};
    SDL_RenderCopy(renderer, losingTextTexture, NULL, &losingTextRect);

    SDL_FreeSurface(losingTextSurface);
    SDL_DestroyTexture(losingTextTexture);
    TTF_CloseFont(font);

    SDL_RenderPresent(renderer);
    SDL_Delay(3000);
}