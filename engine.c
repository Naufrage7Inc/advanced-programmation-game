#include "engine.h"


bool InitSDL() {
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        fprintf(stderr, "Impossible d'initialiser la SDL : %s\n", SDL_GetError());
        return false;
	}

	return true;
}


bool CreateWindow(SDL_Window** window, const int width, const int height, const char* title) {
    *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if ( *window == NULL ) {
        fprintf(stderr, "Impossible de créer la fenêtre de jeu : %s\n", SDL_GetError());
        return false;
    }

    return true;
}


bool CreateWindowSurface(SDL_Surface** surface, const SDL_Window* window) {
    *surface = SDL_GetWindowSurface(window);
    if ( surface == NULL ) {
        fprintf(stderr, "Impossible de créer la surface de la fenêtre : %s\n", SDL_GetError());
        return false;
    }

    return true;
}


void CleanupSDL(SDL_Window* window) {
    SDL_DestroyWindow(window);
	SDL_Quit();
}


SDL_Surface* LoadBMP(const char* imagePath) {
    SDL_Surface* surface = SDL_LoadBMP(imagePath);
    if ( surface == NULL ) {
        fprintf(stderr, "Impossible de charger l'image : %s\n", SDL_GetError());
    }

    return surface;
}
