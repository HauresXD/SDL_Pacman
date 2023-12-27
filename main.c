#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <assert.h>

#include "sdl_playground.h"
// #include "array.h" // ?????? Asi není potřeba


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

typedef struct {
    int w;
    int h;
    int id;
} Wall;

typedef struct {
    int w;
    int h;
    int id;
    int direction; // Right = 0, Down = 1, Left = 2, Up = 3
} Pacman;

void drawGrid(SDL_Renderer *ren) {

    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);

    for (int x = 0; x <= WINDOW_WIDTH; x += GRID_SIZE) {

        SDL_RenderDrawLine(ren, x, 0, x, WINDOW_HEIGHT);
    }

    for (int y = 0; y <= WINDOW_HEIGHT; y += GRID_SIZE) {

        SDL_RenderDrawLine(ren, 0, y, WINDOW_WIDTH, y);
    }
}

void drawWall(SDL_Renderer *renderer, int width, int height, int id, SDL_Rect *walls) {

    SDL_SetRenderDrawColor(renderer, 0, 0, 150, 255);

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

int readFile(SDL_Renderer *ren, Wall *walls, Pacman *pman) {

    FILE *file = fopen("../playground.txt", "rt");
    if(file == NULL) {

        printf("Nenašel se 'playground.txt'\n");
        exit(1);
    }

    char line[20];
    int id = 0;

    // Načíst řádek
    for(int i = 0; i < 12; i++) {

        fgets(line, sizeof(line), file);

        // Znak po znaku
        for(int j = 0; j < 16; j++) {

            // Přidání objektu
            if(line[j] == '#') {

                walls[id].w = j;
                walls[id].h = i;
                walls[id].id = id;

                id += 1;
            }else if(line[j] == 'P') {

                printf("YEEEE");
                pman->w = j;
                pman->h = i;
                pman->id = 0;
                pman->direction = 0;

                id += 1;
            }
        }
    }
    fclose(file);

    return id;
}

int main() {

    SDL_Window *win = NULL;
    SDL_Renderer *ren = NULL;
    
    bool initialized = sdl_playground_init(&win, &ren, WINDOW_WIDTH, WINDOW_HEIGHT);

    if(!initialized) {

        sdl_playground_destroy(win, ren);
        return -1;
    }

    SDL_Texture *pacmanT = IMG_LoadTexture(ren, "../imgs/Pacman.png");
    if(!pacmanT) {

        fprintf(stderr, "Could not load image: %s\n", SDL_GetError());
        return -1;
    }

    // Wall pman = {.w = 1, .h = 1, .id = 0};
    Pacman *pacman = (Pacman *)malloc(1 * sizeof(Pacman));
    Wall *walls = (Wall *)malloc(192 * sizeof(Wall));
    SDL_Rect *wallsDraw = (SDL_Rect *)malloc(192 * sizeof(SDL_Rect));
    int numOfWalls = readFile(ren, walls, pacman);


    int posX = pacman->w*PACMAN_SIZE;
    int posY = pacman->h*PACMAN_SIZE;
    int prevPosX = posX;
    int prevPosY = posY;

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
                    pacman->direction = 2;
                }else if(e.key.keysym.sym == SDLK_RIGHT) {

                    prevPosX = posX;
                    prevPosY = posY;
                    if((posX+PACMAN_SIZE) < WINDOW_WIDTH) {

                        posX += 10;
                    }
                    pacman->direction = 0;
                }else if(e.key.keysym.sym == SDLK_UP) {

                    prevPosX = posX;
                    prevPosY = posY;
                    if(posY != 0) {

                        posY -= 10;
                    }
                    pacman->direction = 3;
                }else if(e.key.keysym.sym == SDLK_DOWN) {

                    prevPosX = posX;
                    prevPosY = posY;
                    if((posY+PACMAN_SIZE) < WINDOW_HEIGHT) {

                        posY += 10;
                    }
                    pacman->direction = 1;
                }
            }
        }

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        drawGrid(ren);

        // Kreslení zdí
        for(int i = 0; i < numOfWalls; i++) {

            drawWall(ren, walls[i].w, walls[i].h, walls[i].id, wallsDraw);
        }

        // 'Pacman'
        SDL_SetRenderDrawColor(ren, 255, 255, 0, 255);
        SDL_Rect pacmanIG = {.x = posX, .y = posY, .w = PACMAN_SIZE, .h = PACMAN_SIZE};
        //                                            Rotace --> může se měnit podle toho, kudy jde
        int pAngle = 0;
        if(pacman->direction == 0) {

            pAngle = 0;
        }else if(pacman->direction == 1) {

            pAngle = 90;
        }else if(pacman->direction == 2) {

            pAngle = 180;
        }else if(pacman->direction == 3) {

            pAngle = 270;
        }
        SDL_RenderCopyEx(ren, pacmanT, NULL, &pacmanIG, pAngle, NULL, 0);

        // Collision
        for(int i = 0; i < numOfWalls; i++) {

            if (SDL_HasIntersection(&pacmanIG, &wallsDraw[i])) {

                posX = prevPosX;
                posY = prevPosY;
            }
        }

        SDL_RenderPresent(ren);
    }

    sdl_playground_destroy(win, ren);


    free(pacman);
    free(walls);
    free(wallsDraw);
    return 0;
}
