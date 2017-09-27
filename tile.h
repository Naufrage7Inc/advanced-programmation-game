#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED


#include <SDL2/SDL.h>

typedef struct {
    SDL_Surface* surface;
    int type;
} Tile;


/* Permet de créer un bloc */
Tile TileCreate( const SDL_Surface* surface, const int type );

#endif // TILE_H_INCLUDED
