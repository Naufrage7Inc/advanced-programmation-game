#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED


#include "engine.h"


/* Structure pour représenter une carte */
typedef struct {
    Size size;
    SDL_Surface* surface;
} Map;


#endif // MAP_H_INCLUDED
