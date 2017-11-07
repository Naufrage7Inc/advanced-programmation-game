#include "tile.h"
#include "engine.h"


Tile* TileCreate( SDL_Surface* surface, const Passability passability )  {
    Tile* tile = (Tile*) malloc_trace( sizeof( Tile ) );
    tile->surface = surface;
    tile->passability = passability;

    return tile;
}

void TileFree( Tile* tile ) {
    SDL_FreeSurface( tile->surface );
    free_trace( tile );
}
