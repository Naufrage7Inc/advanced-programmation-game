#include "tile.h"


Tile* TileCreate( SDL_Surface* surface, const Passability passability )  {
    /* TODO */
    Tile* tile = malloc( sizeof( Tile ) );
    tile->surface = surface;
    tile->passability = passability;

    return tile;
}
