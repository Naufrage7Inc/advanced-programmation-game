#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED


#include "engine.h"
#include "tile.h"


/* Structure pour représenter une carte */
typedef struct {
    Size size;
    SDL_Surface* surface;
    SDL_Surface* surfaceTileset;
    Tile tiles[N_BLOCKS_Y][N_BLOCKS_X];
} Map;


/* Permet de créer une carte */
Map MapCreate( const char* imagePath );


/* Libère la mémoire ( notamment les SDL_Surface* des tiles ) */
void MapFree( Map* map );

#endif // MAP_H_INCLUDED
