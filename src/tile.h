#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include <SDL2/SDL.h>


/* Structure pour contenir un bloc de terrain */
typedef struct {
    SDL_Surface *surface;
} Tile;


/* Permet de créer un bloc */
Tile* TileCreate( SDL_Surface *surface );

/* Libère un bloc */
void  TileFree( Tile *tile );


#endif // TILE_H_INCLUDED
