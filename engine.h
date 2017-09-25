#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED


#include <stdbool.h>

#include <SDL2/SDL.h>


/* Structure pour contenir une coordonée représentée par un point X et un point Y */
typedef struct {
    int x;
    int y;
} Coords;


/* Strucutre pour contenir une taille représentée par sa longueur et sa hauteur */
typedef struct {
    int w;
    int h;
} Size;


/* Permet d'initialiser la SDL */
bool InitSDL();


/* Permet de créer une fenêtre graphique */
bool CreateWindow(SDL_Window** window, const int width, const int height, const char* title);


/* Permet de créer la surface de la fenêtre */
bool CreateWindowSurface(SDL_Surface** surface, const SDL_Window* window);


/* Permet de nettoyer la fenêtre et de décharger la SDL */
void CleanupSDL(SDL_Window* window);


/* Permet de charger une image en mémoire */
SDL_Surface* LoadBMP(const char* imagePath);

#endif // ENGINE_H_INCLUDED
