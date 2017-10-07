#include "tile.h"


Tile* TileCreate( SDL_Surface* surface, const int type )  {
    /* TODO */
    Tile* tile = malloc(sizeof(Tile));
    tile->surface = surface;
    tile->type = type;

    return tile;
}
