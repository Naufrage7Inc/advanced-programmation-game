#define WINDOW_WIDTH 768
#define WINDOW_HEIGHT 576
#define WINDOW_TITLE "Projet programmation avancée"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "engine.h"
#include "character.h"
#include "map.h"


int main()
{
    /* Initialisation de la SDL */
    if ( !InitSDL() ) {
        return EXIT_FAILURE;
    }


	/* Création de la fenêtre */
	SDL_Window* window = NULL;
	if ( !CreateWindow(&window, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE) ) {
        SDL_Quit();
        return EXIT_FAILURE;
	}


    /* Création de la surface de la fenêtre */
    SDL_Surface* surfaceWindow = NULL;
    if ( !CreateWindowSurface(&surfaceWindow, window) ) {
        SDL_Quit();
        SDL_DestroyWindow(window);
        return EXIT_FAILURE;
    }


    /* Boucle d'évènements */
    bool isOpen = true;
    SDL_Event event;

	while ( isOpen ) {
        /* SDL_WaitEvent est bloquant */
		SDL_WaitEvent(&event);


        /* Si l'utilisateur décide de fermer la fenêtre */
		if ( event.window.event == SDL_WINDOWEVENT_CLOSE )
			isOpen = false;
    }


	/* Nettoyage */
	CleanupSDL(window);


    /* Si on arrive jusqu'ici, c'est génial */
    return EXIT_SUCCESS;
}
