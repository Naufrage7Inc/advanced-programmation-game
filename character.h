#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include <SDL2/SDL.h>

#include "engine.h"


/* Structure pour représenter un personnage */
typedef struct {
    Coords position;
    Size size;
    SDL_Surface* surface;
    SDL_Rect srcRect;
} Character;


#endif // CHARACTER_H_INCLUDED
