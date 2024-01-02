#ifndef STRUCTS_H_
#define STRUCTS_H_

    typedef struct {
        int id;
        int w;
        int h;
        int direction;
        int killable;
        int killed;
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

#endif