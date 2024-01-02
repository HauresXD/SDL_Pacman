#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

#include "structs.h"
#include "sdl_playground.h"
#include "ghosts.h"
#include "points.h"
#include "walls.h"
#include "files.h"
#include "screens.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define DEF_SIZE 50
#define GRID_SIZE 50
#define FONT_PATH "../arial.ttf"
#define FONT_SIZE 24

int main() {

    srand((unsigned int)time(NULL));

    SDL_Window *win = NULL;
    SDL_Renderer *ren = NULL;
    
    bool initialized = sdl_playground_init(&win, &ren, WINDOW_WIDTH, WINDOW_HEIGHT);

    if(!initialized) {

        sdl_playground_destroy(win, ren);
        return -1;
    }

    // Pacman and Grave load texture check
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

    // Font load check
    if(TTF_Init() == -1) {

        fprintf(stderr, "TTF_Init: %s\n", TTF_GetError());
        return -1;
    }
    TTF_Font *font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
    if(!font) {

        fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());
        return -1;
    }

    int bestScore = readBestScore();

    // Render menu
    int menuResult = mainMenu(ren, font, bestScore);
    if(menuResult != 0) {
        
        sdl_playground_destroy(win, ren);

        SDL_DestroyTexture(pacmanT);
        TTF_CloseFont(font);
        TTF_Quit();

        return -1;
    }

    // --- Pacman
    Pacman *pacman = (Pacman *)malloc(1 * sizeof(Pacman));
    // --- Walls
    Wall *walls = (Wall *)malloc(192 * sizeof(Wall));
    SDL_Rect *wallsDraw = (SDL_Rect *)malloc(192 * sizeof(SDL_Rect));
    // --- Ghost spawn
    GhostSpawn *gSpawn = (GhostSpawn *)malloc((1 * sizeof(GhostSpawn)));
    // --- Ghosts
    Ghost *ghosts = (Ghost *)malloc(4 * sizeof(Ghost));
    SDL_Rect *ghostsDraw = (SDL_Rect *)malloc(4 * sizeof(SDL_Rect));
    SDL_Texture *ghostsTextures[4];
    // --- Points
    Point *points = (Point *)malloc(192 * sizeof(Point));
    SDL_Rect *pointsDraw = (SDL_Rect *)malloc(192 * sizeof(SDL_Rect));
    // --- Special points
    Special *specialPoints = (Special *)malloc(4 * sizeof(Special));
    SDL_Rect *specialPointsDraw = (SDL_Rect *)malloc(4 * sizeof(SDL_Rect));

    int numOfWalls = readFile(ren, walls, pacman, gSpawn, specialPoints, points);

    for(int i = 0; i < 4; i++) {

        ghosts[i].id = i;
        ghosts[i].h = gSpawn->h;
        ghosts[i].w = gSpawn->w;
        ghosts[i].direction = 0;
        ghosts[i].killable = 0;
        ghosts[i].killed = 0;
    }

    int posX = pacman->w*DEF_SIZE;
    int posY = pacman->h*DEF_SIZE;
    int prevPosX = posX;
    int prevPosY = posY;
    int origPosX = posX;
    int origPosY = posY;

    SDL_Color textColor = {255, 255, 255};

    int CPOINTS = 0;
    int LIVES = 3;

    int canKill = 0;
    int time = 0;
    int ghost0Timer = 0;
    int ghost1Timer = 0;
    int ghost2Timer = 0;
    int ghost3Timer = 0;
    int ghostsMove = 0;

    SDL_Event e;
    bool RUN = true;
    while(RUN) {

        while(SDL_PollEvent(&e)) {

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

        // Ghost Movement
        moveGhosts(ghosts, walls, numOfWalls, posX/DEF_SIZE, posY/DEF_SIZE, ghostsMove, *gSpawn);

        // Draw walls
        for(int i = 0; i < numOfWalls; i++) {

            drawWall(ren, walls[i].w, walls[i].h, walls[i].id, wallsDraw);
        }

        // Draw sPoints
        for(int i = 0; i < 4; i++) {

            placeSpecialPoints(ren, specialPoints[i].x, specialPoints[i].y, i, specialPointsDraw, specialPoints);
        }

        // Draw points
        for(int i = 0; i < 192-numOfWalls; i++) {

            placePoints(ren, points[i].x, points[i].y, i, pointsDraw, points);
        }

        // Draw ghosts
        for(int i = 0; i < 4; i++) {

            drawGhosts(ren, ghostsDraw, ghosts, ghostsTextures);
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

        // Collision with walls
        for(int i = 0; i < numOfWalls; i++) {

            if(SDL_HasIntersection(&pacmanIG, &wallsDraw[i])) {

                posX = prevPosX;
                posY = prevPosY;
            }
        }

        // Touched ghost
        for(int i = 0; i < 4; i++) {

            if(SDL_HasIntersection(&pacmanIG, &ghostsDraw[i])) {

                if(ghosts[i].killable == 0) {
                    
                    LIVES -= 1;
                    posX = origPosX;
                    posY = origPosY;
                    for(int i = 0; i < 4; i++) {

                        ghosts[i].w = gSpawn->w;
                        ghosts[i].h = gSpawn->h;
                    }
                }else if(ghosts[i].killable == 1) {
                    
                    ghosts[i].killed = 1;
                    if(i == 0) {

                        ghost0Timer = 0;
                    }else if(i == 1) {

                        ghost1Timer = 0;
                    }else if(i == 2) {

                        ghost2Timer = 0;
                    }else if(i == 3) {

                        ghost3Timer = 0;
                    }
                    if(time >= 5 * 23) { 

                        ghosts[i].killable = 0;
                    }

                }
            }
        }

        // Time ghost revival
        for(int i = 0; i < 4; i++) {

            if(ghosts[i].killed == 1) {

                if(i == 0) {

                    if(ghost0Timer > 5*23) {

                        ghosts[i].killed = 0;
                    }
                }else if(i == 1) {

                    if(ghost1Timer > 5*23) {

                        ghosts[i].killed = 0;
                    }
                }else if(i == 2) {

                    if(ghost2Timer > 5*23) {

                        ghosts[i].killed = 0;
                    }
                }else if(i == 3) {

                    if(ghost3Timer > 5*23) {

                        ghosts[i].killed = 0;
                    }
                }
            }
        }

        // LIVES check
        if(LIVES <= 0) {

            losingScreen(ren, CPOINTS);
            RUN = 0;
        }

        // Collect Specials
        for(int i = 0; i < 4; i++) {

            if(SDL_HasIntersection(&pacmanIG, &specialPointsDraw[i]) && specialPoints[i].skip != 1) {

                delSpecialPoints(i, specialPoints);
                canKill = 1;
                for(int i = 0; i < 4; i++) {

                    ghosts[i].killable = 1;
                }
                time = 0;
            }
        }

        // Collect Points
        for(int i = 0; i < 192-numOfWalls; i++) {

            if(SDL_HasIntersection(&pacmanIG, &pointsDraw[i]) && points[i].skip != 1) {

                CPOINTS += 1;
                delPoint(i, points, 192-numOfWalls);
            }
            if(CPOINTS == 192-6-numOfWalls) {

                winningScreen(ren);
            }
        }

        // Make text
        char livesStatus[15];
        char pointsStatus[15];
        sprintf(pointsStatus, "Points: %d |", CPOINTS);
        sprintf(livesStatus, "Lives: %d", LIVES);

        // Printf points 
        SDL_Surface *pointsTextSurface = TTF_RenderText_Solid(font, pointsStatus, textColor);
        SDL_Texture *pointsTextTexture = SDL_CreateTextureFromSurface(ren, pointsTextSurface);
        SDL_Rect pointsTextRect = {.x = 0, .y = 0, .w = pointsTextSurface->w, .h = pointsTextSurface->h};
        SDL_RenderCopy(ren, pointsTextTexture, NULL, &pointsTextRect);

        // Printf lives
        SDL_Surface *livesTextSurface = TTF_RenderText_Solid(font, livesStatus, textColor);
        SDL_Texture *livesTextTexture = SDL_CreateTextureFromSurface(ren, livesTextSurface);
        SDL_Rect livesTextRect = {.x = 140, .y = 0, .w = livesTextSurface->w, .h = livesTextSurface->h};
        SDL_RenderCopy(ren, livesTextTexture, NULL, &livesTextRect);

        SDL_FreeSurface(pointsTextSurface);
        SDL_DestroyTexture(pointsTextTexture);
        SDL_FreeSurface(livesTextSurface);
        SDL_DestroyTexture(livesTextTexture);

        // Ghost kill timer ?
        if(canKill == 1) {

            if(time > 5*23) {  

                canKill = 0;
                for(int i = 0; i < 4; i++) {
                    
                    ghosts[i].killable = 0;
                }
            }
        }

        time++;
        ghost0Timer++;
        ghost1Timer++;
        ghost2Timer++;
        ghost3Timer++;
        ghostsMove++;
        SDL_RenderPresent(ren);
    }
    sdl_playground_destroy(win, ren);

    SDL_DestroyTexture(pacmanT);
    for (int i = 0; i < 4; i++) {

        SDL_DestroyTexture(ghostsTextures[i]);
    }

    TTF_CloseFont(font);
    TTF_Quit();

    // Write new score
    if(bestScore < CPOINTS) {

        writeBestScore(CPOINTS);
    }

    // Free & Return
    free(points);
    free(pointsDraw);
    free(specialPoints);
    free(specialPointsDraw);
    free(gSpawn);
    free(ghosts);
    free(ghostsDraw);
    free(pacman);
    free(walls);
    free(wallsDraw);
    return 0;
}