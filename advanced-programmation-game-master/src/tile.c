#include "tile.h"
#include "engine.h"


Tile* TileCreate( SDL_Surface *surface ) {
    Tile *tile = (Tile *) malloc( sizeof( Tile ) );

    tile->surface = surface;

    return tile;
}

void TileFree( Tile *tile ) {
    SDL_FreeSurface( tile->surface );
    free( tile );
}
