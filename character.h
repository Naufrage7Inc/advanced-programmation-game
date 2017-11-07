#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include <SDL2/SDL.h>

#include "engine.h"
#include "map.h"
#include "liste.h"


/* Enumération pour les directions */
typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;


/* Structure pour représenter un personnage */
typedef struct {
    SDL_Surface *surfaceTileset;
    SDL_Rect     rectSrc;
    Coord        position;
    Direction    direction;
} Character;


/* Permet de créer un personnage */
Character* CharacterCreate(const char *imagePath,
                           const Coord position);


/* Permet de dessiner le personnage sur une surface ( généralement l'écran ) */
void CharacterDraw(const Character *character,
                   SDL_Surface     *surface);


/* Permet de déplacer un personnage sur la carte */
void CharacterMove(Character      *character,
                   const Direction direction);


/* Permet de libérer de la mémoire */
void CharacterFree(Character *character);


/* Permet de récupérer la position du joueur */
Coord CharacterGetCoord(Character *character);


/* */
void CharacterSetCoord(Character* character, Coord position);


/* */
bool IsThereCharacterAtPosition(const Coord position,
                                Character  *character,
                                TList characters,
                                int         n);


#endif // CHARACTER_H_INCLUDED
