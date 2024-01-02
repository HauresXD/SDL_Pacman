#include "files.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define DEF_SIZE 50
#define GRID_SIZE 50

int readFile(SDL_Renderer *ren, Wall *walls, Pacman *pman, GhostSpawn *gSpawn, Special *sPoints, Point *points) {

    FILE *file = fopen("../map.txt", "rt");
    if(file == NULL) {

        printf("Nenašel se 'map.txt'\n");
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

int readBestScore() {

    FILE *bestSocre = fopen("../bestScore.txt", "rt");
    char line[10];

    fgets(line, sizeof(line), bestSocre);
    fclose(bestSocre);

    return atoi(line);
}

void writeBestScore(int new) {

    FILE *bestScore = fopen("../bestScore.txt", "wt");

    fprintf(bestScore, "%d", new);
    fclose(bestScore);    
}
