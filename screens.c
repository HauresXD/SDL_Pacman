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

void renderMainMenu(SDL_Renderer *renderer, TTF_Font *font, int highestScore) {

    SDL_Color textColor = {255, 255, 255};

    char pacmanText[] = "Pacman";
    SDL_Surface *pacmanTextSurface = TTF_RenderText_Solid(font, pacmanText, textColor);
    SDL_Texture *pacmanTextTexture = SDL_CreateTextureFromSurface(renderer, pacmanTextSurface);
    SDL_Rect pacmanTextRect = {.x = WINDOW_WIDTH / 2 - pacmanTextSurface->w / 2, .y = WINDOW_HEIGHT / 2 - pacmanTextSurface->h, .w = pacmanTextSurface->w, .h = pacmanTextSurface->h};
    SDL_RenderCopy(renderer, pacmanTextTexture, NULL, &pacmanTextRect);

    char startGameText[] = "Zacit hru";
    SDL_Surface *startGameTextSurface = TTF_RenderText_Solid(font, startGameText, textColor);
    SDL_Texture *startGameTextTexture = SDL_CreateTextureFromSurface(renderer, startGameTextSurface);
    SDL_Rect startGameTextRect = {.x = WINDOW_WIDTH / 2 - startGameTextSurface->w / 2, .y = WINDOW_HEIGHT / 2 + 50, .w = startGameTextSurface->w, .h = startGameTextSurface->h};
    SDL_RenderCopy(renderer, startGameTextTexture, NULL, &startGameTextRect);

    char highestScoreText[50];
    sprintf(highestScoreText, "Nejvyssi skore: %d", highestScore);
    SDL_Surface *highestScoreTextSurface = TTF_RenderText_Solid(font, highestScoreText, textColor);
    SDL_Texture *highestScoreTextTexture = SDL_CreateTextureFromSurface(renderer, highestScoreTextSurface);
    SDL_Rect highestScoreTextRect = {.x = WINDOW_WIDTH / 2 - highestScoreTextSurface->w / 2, .y = WINDOW_HEIGHT / 2 + 100, .w = highestScoreTextSurface->w, .h = highestScoreTextSurface->h};
    SDL_RenderCopy(renderer, highestScoreTextTexture, NULL, &highestScoreTextRect);

    SDL_FreeSurface(pacmanTextSurface);
    SDL_DestroyTexture(pacmanTextTexture);
    SDL_FreeSurface(startGameTextSurface);
    SDL_DestroyTexture(startGameTextTexture);
    SDL_FreeSurface(highestScoreTextSurface);
    SDL_DestroyTexture(highestScoreTextTexture);
}

int mainMenu(SDL_Renderer *renderer, TTF_Font *font, int highestScore) {
    
    SDL_Event e;
    while(1) {

        while(SDL_PollEvent(&e)) {

            if(e.type == SDL_QUIT) {

                return -1;
            }else if(e.type == SDL_KEYDOWN) {

                if(e.key.keysym.sym == SDLK_ESCAPE) {

                    return -1;
                }
            }else if(e.type == SDL_MOUSEBUTTONDOWN) {

                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                if(mouseX >= WINDOW_WIDTH / 2 - 100 && mouseX <= WINDOW_WIDTH / 2 + 100 && mouseY >= WINDOW_HEIGHT / 2 + 50 && mouseY <= WINDOW_HEIGHT / 2 + 100 + 50) {
                   
                    return 0;  
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        renderMainMenu(renderer, font, highestScore);
        SDL_RenderPresent(renderer);
    }
}
