#include "constants.h"
#include "engine.h"
#include "map.h"


Map* MapCreate( const char* imagePath, const char* filePath ) {
    Map* map = malloc( sizeof( Map ) );

    map->surfaceTileset = LoadBMP( imagePath );

    FILE* fdHandle = fopen( filePath, "rb" );

    if ( fdHandle == NULL ) {
        fprintf( stderr, "Unable to open %s\n", filePath );
        SDL_FreeSurface( map->surfaceTileset );
        free( map );
        return NULL;
    }

    for ( int y = 0; y < N_BLOCKS_Y; y++ ) {
        for ( int x = 0; x < N_BLOCKS_X; x++ ) {
            int id = 0;
            fread( &id, sizeof( int ), 1, fdHandle );
            map->tiles[y][x] = TileCreate( SurfaceGetResource( map->surfaceTileset, 12, id ), PASSABLE );
        }
    }

    return map;
}


void MapDraw( const Map* map, SDL_Surface* surface ) {
    for ( int y = 0; y < N_BLOCKS_Y; y++ ) {
        for ( int x = 0; x < N_BLOCKS_X; x++ ) {
            SDL_Rect dst = {x * SIZE_BLOCK, y * SIZE_BLOCK, SIZE_BLOCK, SIZE_BLOCK};
            SDL_BlitSurface( map->tiles[y][x]->surface, NULL, surface, &dst );
        }
    }
}


void MapFree( Map* map ) {
    for ( int y = 0; y < N_BLOCKS_Y; y++ ) {
        for ( int x = 0; x < N_BLOCKS_X; x++ ) {
            SDL_FreeSurface( map->tiles[y][x]->surface );
        }
    }

    SDL_FreeSurface( map->surfaceTileset );
    free( map );
}
