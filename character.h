#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include <SDL2/SDL.h>

#include "engine.h"


/* Enumération pour les directions */
enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
};


/* Structure pour représenter un personnage */
typedef struct {
    Coord position;
    SDL_Surface* surface;
    SDL_Rect srcRect;
    int direction;
} Character;


/* Permet de créer un personnage */
Character CharacterCreate( const char* imagePath, const Coord position );


/* Permet de dessiner le personnage sur une surface ( généralement l'écran ) */
void CharacterDraw( const Character* character, SDL_Surface* surface );


/* Permet de déplacer un personnage sur la carte */
void CharacterMove( Character* character, int direction );


#endif // CHARACTER_H_INCLUDED
