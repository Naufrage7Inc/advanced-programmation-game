#define WINDOW_WIDTH 768
#define WINDOW_HEIGHT 576
#define WINDOW_TITLE "Projet programmation avancée"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "engine.h"
#include "character.h"


int main()
{
    /* Initialisation de la SDL */
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        fprintf(stderr, "Impossible de charger la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
	}


	/* Création de la fenêtre */
	SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if ( window == NULL ) {
        fprintf(stderr, "Impossible de créer la fenêtre de jeu : %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }


    /* Création de la surface de la fenêtre */
    SDL_Surface* surfaceWindow = SDL_GetWindowSurface(window);
    if ( surfaceWindow == NULL ) {
        fprintf(stderr, "Impossible de créer la surface de la fenêtre : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }


    /* Boucle d'évènements */
    bool isOpen = true;
    SDL_Event event;

	while ( isOpen ) {
        /* SDL_WaitEvent est bloquant */
		SDL_WaitEvent(&event);


        /* Si le joueur décide de fermer la fenêtre */
		if ( event.window.event == SDL_WINDOWEVENT_CLOSE )
			isOpen = false;
    }


	/* Nettoyage */
	SDL_DestroyWindow(window);
	SDL_Quit();


    /* Si on arrive jusqu'ici, c'est génial */
    return EXIT_SUCCESS;
}
