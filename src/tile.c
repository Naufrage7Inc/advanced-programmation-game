#include "tile.h"
#include "engine.h"

/* Permet de créer une variable de type Tile */
Tile* TileCreate( SDL_Surface *surface ) {
    Tile *tile = (Tile *) malloc( sizeof( Tile ) );

    tile->surface = surface;

    return tile;
}

/* Permet de libérer un Tile */
void TileFree( Tile *tile ) {
    SDL_FreeSurface( tile->surface );
    free( tile );
}
