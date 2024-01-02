#include "ghosts.h"

#define DEF_SIZE 50
#define GRID_SIZE 50

void drawGhosts(SDL_Renderer *renderer, SDL_Rect *ghostsD, Ghost *ghosts, SDL_Texture *ghostsT[]) {

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for(int i = 0; i < 4; i++) {

        char path[25];

        if(ghosts[i].killable == 0) {

            sprintf(path, "../imgs/ghost_%d.png", i);
        }else {

            strcpy(path, "../imgs/ghost_kill.png");
        }

        ghostsT[i] = IMG_LoadTexture(renderer, path);

        if(!ghostsT[i]) {

            fprintf(stderr, "Nejde načíst obrázek pro ducha %d: %s\n", i, SDL_GetError());
        }

        ghostsD[i].x = ghosts[i].w * DEF_SIZE;
        ghostsD[i].y = ghosts[i].h * DEF_SIZE;
        ghostsD[i].w = DEF_SIZE;
        ghostsD[i].h = DEF_SIZE;

        
        if(ghosts[i].killed == 1) {

        }else {

            SDL_RenderCopy(renderer, ghostsT[i], NULL, &ghostsD[i]);
        }
    }
}

int checkWallCollision(int x, int y, Wall *walls, int numWalls) {

    for(int i = 0; i < numWalls; i++) {

        if(x == walls[i].w && y == walls[i].h) {

            return 1; 
        }
    }
    return 0;
}

void ghostMovement(Ghost *ghosts, Wall *walls, int numWalls, int pacmanX, int pacmanY, int i, GhostSpawn gSpawn) {

    if(ghosts[i].killed == 0) {

        int dx = pacmanX - ghosts[i].w;
        int dy = pacmanY - ghosts[i].h;

        // Zjišťuje kudy má jít
        if(abs(dx) > abs(dy)) {

            if(dx > 0) {

                if(!checkWallCollision(ghosts[i].w + 1, ghosts[i].h, walls, numWalls)) {

                    ghosts[i].w += 1;
                }else{
                    
                    int randomDirection;
                    do{
                        
                        randomDirection = rand() % 4;
                    }while(checkWallCollision(ghosts[i].w + (randomDirection == 0) - (randomDirection == 2),
                                               ghosts[i].h + (randomDirection == 1) - (randomDirection == 3), walls,
                                               numWalls));

                    ghosts[i].w += (randomDirection == 0) - (randomDirection == 2);
                    ghosts[i].h += (randomDirection == 1) - (randomDirection == 3);
                }
            }else {

                if(!checkWallCollision(ghosts[i].w - 1, ghosts[i].h, walls, numWalls)) {

                    ghosts[i].w -= 1;
                }else {
                    int randomDirection;
                    do{

                        randomDirection = rand() % 4;
                    }while(checkWallCollision(ghosts[i].w + (randomDirection == 0) - (randomDirection == 2),
                                               ghosts[i].h + (randomDirection == 1) - (randomDirection == 3), walls,
                                               numWalls));

                    ghosts[i].w += (randomDirection == 0) - (randomDirection == 2);
                    ghosts[i].h += (randomDirection == 1) - (randomDirection == 3);
                }
            }
        }else {

            if(dy > 0) {

                if(!checkWallCollision(ghosts[i].w, ghosts[i].h + 1, walls, numWalls)) {

                    ghosts[i].h += 1;
                }else {

                    int randomDirection;
                    do {

                        randomDirection = rand() % 4;
                    } while(checkWallCollision(ghosts[i].w + (randomDirection == 0) - (randomDirection == 2),
                                               ghosts[i].h + (randomDirection == 1) - (randomDirection == 3), walls,
                                               numWalls));
                                               
                    ghosts[i].w += (randomDirection == 0) - (randomDirection == 2);
                    ghosts[i].h += (randomDirection == 1) - (randomDirection == 3);
                }
            }else {

                if(!checkWallCollision(ghosts[i].w, ghosts[i].h - 1, walls, numWalls)) {

                    ghosts[i].h -= 1;
                }else {

                    int randomDirection;
                    do {

                        randomDirection = rand() % 4;
                    } while (checkWallCollision(ghosts[i].w + (randomDirection == 0) - (randomDirection == 2),
                                               ghosts[i].h + (randomDirection == 1) - (randomDirection == 3), walls,
                                               numWalls));

                    ghosts[i].w += (randomDirection == 0) - (randomDirection == 2);
                    ghosts[i].h += (randomDirection == 1) - (randomDirection == 3);
                }
            }
        }
    }else {

        ghosts[i].w = gSpawn.w;
        ghosts[i].h = gSpawn.h;
        ghosts[i].killed = 0;
        ghosts[i].killable = 0;
    }
}

void moveGhosts(Ghost *ghosts, Wall *walls, int numWalls, int pacmanX, int pacmanY, int frame, GhostSpawn gSpawn) {
    
    for(int i = 0; i < 4; i++) {

        if(i == 0 && frame % 15 == 0) {

            ghostMovement(ghosts, walls, numWalls, pacmanX, pacmanY, 0, gSpawn);
        }else if (i == 1 && frame % 18 == 0) {

            ghostMovement(ghosts, walls, numWalls, pacmanX, pacmanY, 1, gSpawn);
        }else if (i == 2 && frame % 12 == 0) {
            
            ghostMovement(ghosts, walls, numWalls, pacmanX, pacmanY, 2, gSpawn);
        }else if (i == 3 && frame % 20 == 0) {
            
            ghostMovement(ghosts, walls, numWalls, pacmanX, pacmanY, 3, gSpawn);
        }
    }
}
