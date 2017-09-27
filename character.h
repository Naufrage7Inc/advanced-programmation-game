#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED


#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3


#include <SDL2/SDL.h>

#include "engine.h"


/* Structure pour représenter un personnage */
typedef struct {
    Coord position;
    Size size;
    SDL_Surface* surface;
    SDL_Rect srcRect;
    int direction;
} Character;


/* Permet de créer un personnage */
Character CharacterCreate( const SDL_Surface* surface, const Coord position, const Size size );


#endif // CHARACTER_H_INCLUDED
