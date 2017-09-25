#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

int main()
{
    /* Initialisation de la SDL */
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        fprintf(stderr, "Impossible de charger la SDL ...\n");
        return EXIT_FAILURE;
	}

	/* Création de la fenêtre */
	SDL_Window* window = SDL_CreateWindow("Projet programmation avancée", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 768, 576, SDL_WINDOW_SHOWN);

    /* Boucle d'évènements */
    bool isOpen = true;
    SDL_Event event;
	while ( isOpen ) {
		SDL_WaitEvent(&event);

		if ( event.window.event == SDL_WINDOWEVENT_CLOSE )
			isOpen = false;
    }

	/* Nettoyage */
	SDL_DestroyWindow(window);
	SDL_Quit();

    return EXIT_SUCCESS;
}
