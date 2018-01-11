#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED


#include "engine.h"
#include "tile.h"


/* Structure pour représenter une carte */
typedef struct {
    SDL_Surface *surfaceTileset;
    Tile      ***tiles;
} Map;


/* Permet de créer une carte */
Map* MapCreate ( const char *imagePath );


/* Dessine la carte sur la surface ( généralement l'écran ) */
void MapDraw ( const Map *map, SDL_Surface *surface );


/* Libère la mémoire ( notamment les SDL_Surface* des tiles ) */
void MapFree ( Map *map );


#endif // MAP_H_INCLUDED
