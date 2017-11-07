#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED


#include <stdbool.h>

#include <SDL2/SDL.h>


/* Structure pour contenir une coordonnée représentée par un point X et un point
   Y */
typedef struct {
    int x;
    int y;
} Coord;


/* Strucutre pour contenir une taille représentée par sa longueur et sa hauteur
 */
typedef struct {
    int w;
    int h;
} Size;


/* Permet de tracer les appels à malloc */
void* malloc_trace ( size_t __size );


/* Permet de tracer les appels à free */
void free_trace ( void *__ptr );


/* Permet d'initialiser la SDL */
bool InitSDL ( );


/* Permet de créer une fenêtre graphique */
bool CreateWindow ( SDL_Window **window, const int width, const int height, const char *title );


/* Permet de créer la surface de la fenêtre */
bool CreateWindowSurface ( SDL_Surface **surface, SDL_Window *window );


/* Permet de nettoyer la fenêtre et de décharger la SDL */
void CleanupSDL ( SDL_Window *window );


/* Permet de charger une image en mémoire */
SDL_Surface* LoadBMP ( const char *imagePath );


/* Permet de créer une coordonnée */
Coord CoordCreate ( const int x, const int y );


/* Permet de créer une coordonnée */
Size SizeCreate ( const int w, const int h );


/* Permet de créer la surface d'un bloc */
SDL_Surface* SurfaceGetResource ( SDL_Surface *surface, const int nTilesX, const int id );


/* Permet de créer une surface vide */
SDL_Surface* SurfaceCreate ( const int w, const int h );


/* */
int GetDistance ( const Coord a, const Coord b );


#endif // ENGINE_H_INCLUDED
