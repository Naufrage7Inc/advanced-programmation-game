#include "constants.h"
#include "engine.h"


bool InitSDL() {
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        fprintf( stderr, "Impossible d'initialiser la SDL : %s\n", SDL_GetError() );
        return false;
    }

    return true;
}


bool CreateWindow( SDL_Window** window, const int width, const int height, const char* title ) {
    *window = SDL_CreateWindow( title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN );
    if ( *window == NULL ) {
        fprintf( stderr, "Impossible de créer la fenêtre de jeu : %s\n", SDL_GetError() );
        return false;
    }

    return true;
}


bool CreateWindowSurface( SDL_Surface** surface, SDL_Window* window ) {
    *surface = SDL_GetWindowSurface( window );
    if ( surface == NULL ) {
        fprintf( stderr, "Impossible de créer la surface de la fenêtre : %s\n", SDL_GetError() );
        return false;
    }

    return true;
}


void CleanupSDL( SDL_Window* window ) {
    SDL_DestroyWindow( window );
    SDL_Quit();
}


SDL_Surface* LoadBMP( const char* imagePath ) {
    SDL_Surface* surface = SDL_LoadBMP( imagePath );
    if ( surface == NULL ) {
        fprintf( stderr, "Impossible de charger l'image : %s\n", SDL_GetError() );
    }

    return surface;
}


Coord CoordCreate( const int x, const int y ) {
    Coord coord = { x, y };
    return coord;
}


Size SizeCreate( const int w, const int h ) {
    Size size = { w, h };
    return size;
}


SDL_Surface* SurfaceGetResource( SDL_Surface* surface, const int nTilesX, const int id ) {
    int x = id % nTilesX * SIZE_BLOCK;
    int y = id / nTilesX * SIZE_BLOCK;

    SDL_Rect src = { x, y, SIZE_BLOCK, SIZE_BLOCK };
    SDL_Rect dst = {0, 0, SIZE_BLOCK, SIZE_BLOCK};



    SDL_Surface* returnSurface = SurfaceCreate( SIZE_BLOCK, SIZE_BLOCK );
    SDL_BlitSurface( surface, &src, returnSurface, &dst );

    return returnSurface;
}


SDL_Surface* SurfaceCreate( const int w, const int h ) {
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

    return SDL_CreateRGBSurface( 0, w, h, 32, rmask, gmask, bmask, amask );
}
