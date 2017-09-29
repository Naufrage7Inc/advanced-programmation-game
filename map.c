#include "constants.h"
#include "engine.h"
#include "map.h"


Map MapCreate( const char* imagePath ) {
    Map map;

    map.surface = SurfaceCreate( WINDOW_WIDTH, WINDOW_HEIGHT );
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


void MapDraw(  const Map* map, SDL_Surface* surface ) {
    SDL_BlitSurface( map->surface, NULL, surface, NULL );
}


void MapFree( Map* map ) {
    for ( int y = 0; y < N_BLOCKS_Y; y++ ) {
        for ( int x = 0; x < N_BLOCKS_X; x++ ) {
            SDL_FreeSurface( map->tiles[y][x].surface );
        }
    }

    SDL_FreeSurface( map->surface );
}
