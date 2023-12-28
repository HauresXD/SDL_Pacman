#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

#include "sdl_playground.h"
// #include "array.h" // ?????? Asi není potřeba


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define DEF_SIZE 50
#define GRID_SIZE 50
#define FONT_PATH "../arial.ttf"
#define FONT_SIZE 24

typedef struct {
    int id;
    int w;
    int h;
    int direction;
    char *color;
    int killable;
} Ghost;

typedef struct {
    int w;
    int h;
} GhostSpawn;

typedef struct {
    int w;
    int h;
    int id;
} Wall;

typedef struct {
    int w;
    int h;
    int id;
    int direction;
} Pacman;

typedef struct {
    int x;
    int y;
    int id;
    int skip;
} Point;

typedef struct {
    int x;
    int y;
    int id;
    int skip;
}Special;

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

void placeSpecialPoints(SDL_Renderer *renderer, int x, int y, int id, SDL_Rect *sPointsD, Special *sPoints) {

    SDL_SetRenderDrawColor(renderer, 210, 124, 15, 255);

    for (int w = 0; w < WINDOW_WIDTH; w += GRID_SIZE) {

        for (int h = 0; h < WINDOW_HEIGHT; h += GRID_SIZE) {

            if (w / GRID_SIZE == x && h / GRID_SIZE == y) {

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

    for (int w = 0; w < WINDOW_WIDTH; w += GRID_SIZE) {

        for (int h = 0; h < WINDOW_HEIGHT; h += GRID_SIZE) {

            if (w / GRID_SIZE == x && h / GRID_SIZE == y) {

                if(points[id].skip != 1) {

                    SDL_Rect rect = {.x = w+22, .y = h+22, .w = 5, .h = 5};
                    SDL_RenderFillRect(renderer, &rect);
                    pointsD[id] = rect;
                }
            }
        }
    }
}

void delPoint(int id, Point *points) {

    int num = 192;
    for (int i = 0; i < num; i++) {

        if (points[i].id == id) {

            points[i].skip = 1;
            break;
        }
    }
}

void delSpecialPoints(int id, Special *sPoints) {

    int num = 4;
    for (int i = 0; i < num; i++) {

        if (sPoints[i].id == id) {

            sPoints[i].skip = 1;
            break;
        }
    }
}

int readFile(SDL_Renderer *ren, Wall *walls, Pacman *pman, GhostSpawn *gSpawn, Special *sPoints, Point *points) {

    FILE *file = fopen("../playground.txt", "rt");
    if(file == NULL) {

        printf("Nenašel se 'playground.txt'\n");
        exit(1);
    }

    char line[20];
    int id = 0;
    int wasP = 0;
    int wasG = 0;
    int sPointCount = 0;
    int pointsCount = 0;

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

                pman->w = j;
                pman->h = i;
                pman->id = 0;
                pman->direction = 0;

                wasP = 1;
            }else if(line[j] == 'G') {

                gSpawn->w = j;
                gSpawn->h = i;

                wasG = 1;
            }else {

                int randint = rand() % 25;
                if(randint > 22 && sPointCount < 4) {

                    sPoints[sPointCount].x = j;
                    sPoints[sPointCount].y = i;
                    sPoints[sPointCount].id = sPointCount;

                    sPointCount += 1;
                }else {

                    points[pointsCount].x = j;
                    points[pointsCount].y = i;
                    points[pointsCount].id = pointsCount;

                    pointsCount += 1;
                }
            }
        }

        if(wasP == 0) {

            pman->w = 1;
            pman->h = 1;
            pman->id = 0;
            pman->direction = 0;
        }
        if(wasG == 0) {

            gSpawn->w = 10;
            gSpawn->h = 10;
        }
    }
    fclose(file);

    return id;
}

int main() {

    srand((unsigned int)time(NULL));

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
    SDL_Texture *gSpawnT = IMG_LoadTexture(ren, "../imgs/grave.png");
    if(!gSpawnT) {

        fprintf(stderr, "Could not load image: %s\n", SDL_GetError());
        return -1;
    }

    if (TTF_Init() == -1) {

        fprintf(stderr, "TTF_Init: %s\n", TTF_GetError());
        return -1;
    }

    TTF_Font *font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
    if (!font) {
        fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());
        return -1;
    }

    Pacman *pacman = (Pacman *)malloc(1 * sizeof(Pacman));
    Wall *walls = (Wall *)malloc(192 * sizeof(Wall));
    GhostSpawn *gSpawn = (GhostSpawn *)malloc((1 * sizeof(GhostSpawn)));
    SDL_Rect *wallsDraw = (SDL_Rect *)malloc(192 * sizeof(SDL_Rect));
    Ghost *ghosts = (Ghost *)malloc(4 * sizeof(Ghost));
    Point *points = (Point *)malloc(192 * sizeof(Point));
    SDL_Rect *pointsDraw = (SDL_Rect *)malloc(192 * sizeof(SDL_Rect));
    Special *specialPoints = (Special *)malloc(4 * sizeof(Special));
    SDL_Rect *specialPointsDraw = (SDL_Rect *)malloc(4 * sizeof(SDL_Rect));

    int numOfWalls = readFile(ren, walls, pacman, gSpawn, specialPoints, points);

    int posX = pacman->w*DEF_SIZE;
    int posY = pacman->h*DEF_SIZE;
    int prevPosX = posX;
    int prevPosY = posY;

    SDL_Color textColor = {255, 255, 255};

    int currPoints = 0;

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
                    if((posX+DEF_SIZE) < WINDOW_WIDTH) {

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
                    if((posY+DEF_SIZE) < WINDOW_HEIGHT) {

                        posY += 10;
                    }
                    pacman->direction = 1;
                }
            }
        }

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);
        drawGrid(ren);

        // Draw walls
        for(int i = 0; i < numOfWalls; i++) {

            drawWall(ren, walls[i].w, walls[i].h, walls[i].id, wallsDraw);
        }

        // Draw sPoints
        for(int i = 0; i < 4; i++) {

            placeSpecialPoints(ren, specialPoints[i].x, specialPoints[i].y, i, specialPointsDraw, specialPoints);
        }

        // Draw points
        for(int i = 0; i < 192; i++) {

            placePoints(ren, points[i].x, points[i].y, i, pointsDraw, points);
        }

        // Grave
        SDL_Rect gSpawnIG = {.x = gSpawn->w*DEF_SIZE, .y = gSpawn->h*DEF_SIZE, .w = DEF_SIZE, .h = DEF_SIZE};
        SDL_RenderCopyEx(ren, gSpawnT, NULL, &gSpawnIG, 0, NULL, 0);

        // Pacman
        SDL_SetRenderDrawColor(ren, 255, 255, 0, 255);
        SDL_Rect pacmanIG = {.x = posX, .y = posY, .w = DEF_SIZE, .h = DEF_SIZE};
        // Pacman movement
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

            if(SDL_HasIntersection(&pacmanIG, &wallsDraw[i])) {

                posX = prevPosX;
                posY = prevPosY;
            }
        }

        // Collect Specials
        for(int i = 0; i < 4; i++) {

            if(SDL_HasIntersection(&pacmanIG, &specialPointsDraw[i]) && specialPoints[i].skip != 1) {

                delSpecialPoints(i, specialPoints);
            }
        }

        // Collect Points
        for(int i = 0; i < 192; i++) {

            if(SDL_HasIntersection(&pacmanIG, &pointsDraw[i]) && points[i].skip != 1) {

                currPoints += 1;
                delPoint(i, points);
            }
        }

        char pointsStatus[15];
        sprintf(pointsStatus, "Points: %d", currPoints);

        // Printf points
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, pointsStatus, textColor);
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(ren, textSurface);
        SDL_Rect textRect = {.x = 0, .y = 0, .w = textSurface->w, .h = textSurface->h};
        SDL_RenderCopy(ren, textTexture, NULL, &textRect);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);

        SDL_RenderPresent(ren);
    }

    sdl_playground_destroy(win, ren);


    TTF_CloseFont(font);
    TTF_Quit();

    // Free & Return
    free(points);
    free(pointsDraw);
    free(specialPoints);
    free(specialPointsDraw);
    free(gSpawn);
    free(ghosts);
    free(pacman);
    free(walls);
    free(wallsDraw);
    return 0;
}
