#include "constants.h"
#include "engine.h"
#include "map.h"


Map* MapCreate( const char *imagePath ) {
    Map *map = malloc( sizeof( Map ) );

    map->tiles = (Tile ***) malloc( N_BLOCKS_Y * sizeof( Tile * * ) );

    for ( int y = 0; y < N_BLOCKS_Y; y++ ) map->tiles[y] = (Tile **) malloc( N_BLOCKS_X * sizeof( Tile * ) );

    map->surfaceTileset = LoadBMP( imagePath );

    for ( int y = 0; y < N_BLOCKS_Y; y++ ) {
        for ( int x = 0; x < N_BLOCKS_X; x++ ) {
            if ( (y == 0) && ((x == 0) || (x == N_BLOCKS_X - 1)) || (y == N_BLOCKS_Y - 1) && ((x == 0) || (x == N_BLOCKS_X - 1)) ) {
                map->tiles[y][x] = TileCreate( SurfaceGetResource( map->surfaceTileset, 1, 3 ) );
            } else {
                map->tiles[y][x] = TileCreate( SurfaceGetResource( map->surfaceTileset, 1, 0 ) );
            }
        }
    }

    return map;
}

void MapDraw( const Map *map, SDL_Surface *surface ) {
    for ( int y = 0; y < N_BLOCKS_Y; y++ ) {
        for ( int x = 0; x < N_BLOCKS_X; x++ ) {
            SDL_Rect dst =
            {x *SIZE_BLOCK, y * SIZE_BLOCK, SIZE_BLOCK, SIZE_BLOCK};
            SDL_BlitSurface( map->tiles[y][x]->surface, NULL, surface, &dst );
        }
    }
}

void MapFree( Map *map ) {
    for ( int y = 0; y < N_BLOCKS_Y; y++ ) {
        for ( int x = 0; x < N_BLOCKS_X; x++ ) {
            TileFree( map->tiles[y][x] );
        }

        free( map->tiles[y] );
    }

    free( map->tiles );

    SDL_FreeSurface( map->surfaceTileset );
    free( map );
}
