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
