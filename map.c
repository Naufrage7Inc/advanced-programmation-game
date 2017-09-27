#include "constants.h"
#include "map.h"


Map MapCreate( const char* imagePath ) {
    Map map;

    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    map.surface = SDL_CreateRGBSurface( 0, WINDOW_WIDTH, WINDOW_HEIGHT, 32, rmask, gmask, bmask, amask );
    map.surfaceTileset = LoadBMP( imagePath );

    for ( int y = 0; y < N_BLOCKS_Y; y++ ) {
        for ( int x = 0; x < N_BLOCKS_X; x++ ) {
            map.tiles[y][x] = TileCreate( SurfaceGetResource( map.surfaceTileset, 8, 17 ), 0 );

            SDL_Rect dst = {x * SIZE_BLOCK, y * SIZE_BLOCK, SIZE_BLOCK, SIZE_BLOCK};
            SDL_BlitSurface( map.tiles[y][x].surface, NULL, map.surface, &dst );
        }
    }

    return map;
}


void MapFree( Map* map ) {
    for ( int y = 0; y < N_BLOCKS_Y; y++ ) {
        for ( int x = 0; x < N_BLOCKS_X; x++ ) {
            SDL_FreeSurface( map->tiles[y][x].surface );
        }
    }

    SDL_FreeSurface( map->surface );
}
