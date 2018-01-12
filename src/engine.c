#include <stdlib.h>
#include <stdio.h>

#include "constants.h"
#include "engine.h"

/* Permet d'initialiser la SDL en mode vidéo. Retourne vrai en cas de réussite */
bool InitSDL( ) {
    if ( SDL_Init ( SDL_INIT_VIDEO ) < 0 ) {
        fprintf ( stderr, "Impossible d'initialiser la SDL : %s\n", SDL_GetError ( ) );
        return false;
    }

    return true;
}

/*  Permet de créer une fenêtre *window* de largeur *width*, de hauteur *height* et de titre *title*. Retourne vrai en cas de réussite */
bool CreateWindow( SDL_Window **window, const int    width, const int    height, const char  *title ) {
    *window = SDL_CreateWindow ( title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN );

    if ( *window == NULL ) {
        fprintf ( stderr, "Impossible de créer la fenêtre de jeu : %s\n", SDL_GetError ( ) );
        return false;
    }

    return true;
}

/* Permet de récupérer la *surface* surface d'une fenêtre *window* créée. Retourne vrai en cas de réussite */
bool CreateWindowSurface( SDL_Surface **surface, SDL_Window *window ) {
    *surface = SDL_GetWindowSurface ( window );

    if ( *surface == NULL ) {
        fprintf ( stderr, "Impossible de créer la surface de la fenêtre : %s\n", SDL_GetError ( ) );
        return false;
    }

    return true;
}

/* Permet de détruire la fenêtre *window* et décharger la SDL */
void CleanupSDL( SDL_Window *window ) {
    SDL_DestroyWindow ( window );
    SDL_Quit ( );
}

/* Retourne une image *imagePath* ( format .bmp ) */
SDL_Surface* LoadBMP( const char *imagePath ) {
    SDL_Surface *surface = SDL_LoadBMP ( imagePath );

    if ( surface == NULL ) {
        fprintf ( stderr, "Impossible de charger l'image : %s\n", SDL_GetError ( ) );
    }

    return surface;
}

/* Retourne une coordonnée ( *x*, *y* ) */
Coord CoordCreate( const int x, const int y ) {
    Coord coord = { x, y };

    return coord;
}

/* Retourne une taille de longueur *w* et de hauteur *h* */
Size SizeCreate( const int w, const int h ) {
    Size size = { w, h };

    return size;
}

/* Retourne l'image de la ressource *id* depuis une surface *surface* ayant *nTilesX* tiles sur la longueur */
SDL_Surface* SurfaceGetResource( SDL_Surface *surface, const int    nTilesX, const int    id ) {
    int x = id % nTilesX * SIZE_BLOCK;
    int y = id / nTilesX * SIZE_BLOCK;

    SDL_Rect src = { x, y, SIZE_BLOCK, SIZE_BLOCK };
    SDL_Rect dst = { 0, 0, SIZE_BLOCK, SIZE_BLOCK };

    SDL_Surface *returnSurface = SurfaceCreate ( SIZE_BLOCK, SIZE_BLOCK );

    SDL_BlitSurface ( surface, &src, returnSurface, &dst );

    return returnSurface;
}

/* Retourne une surface vierge de longueur *w* et de hauteur *h* */
SDL_Surface* SurfaceCreate( const int w, const int h ) {
    Uint32 rmask, gmask, bmask, amask;

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
    #else /* if SDL_BYTEORDER == SDL_BIG_ENDIAN */
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
    #endif /* if SDL_BYTEORDER == SDL_BIG_ENDIAN */

    return SDL_CreateRGBSurface ( 0, w, h, 32, rmask, gmask, bmask, amask );
}

/* Permet de retourner la valeur de la distance entre a et b */
int GetDistance( const Coord a, const Coord b ) {
    return abs ( a.x - b.x ) + ( a.y - b.y );
}
