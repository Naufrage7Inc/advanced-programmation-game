#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED


#include <SDL2/SDL.h>


/* Enumération pour définir la franchissabilité du bloc */
typedef enum {
    NO_PASSABLE,
    PASSABLE
} Passability;


/* Structure pour contenir un bloc de terrain */
typedef struct {
    SDL_Surface* surface;
    Passability passability;
} Tile;


/* Permet de créer un bloc */
Tile* TileCreate( SDL_Surface* surface, const Passability passability );
void TileFree( Tile* tile );


#endif // TILE_H_INCLUDED
