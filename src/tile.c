#include "tile.h"
#include "engine.h"


/* Retourne un morceau de terrain */
Tile* TileCreate( SDL_Surface *surface ) {
    Tile *tile = (Tile *) malloc( sizeof( Tile ) );

    tile->surface = surface;

    return tile;
}


/* Libère le morceau de terrain */
void TileFree( Tile *tile ) {
    SDL_FreeSurface( tile->surface );
    free( tile );
}
