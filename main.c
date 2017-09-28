
#define WINDOW_TITLE "Projet programmation avancée"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "constants.h"
#include "engine.h"
#include "character.h"
#include "map.h"


int main() {
    /* Initialisation de la SDL */
    if ( !InitSDL() ) {
        return EXIT_FAILURE;
    }


    /* Création de la fenêtre */
    SDL_Window* window = NULL;
    if ( !CreateWindow( &window, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE ) ) {
        SDL_Quit();
        return EXIT_FAILURE;
    }


    /* Création de la surface de la fenêtre */
    SDL_Surface* surfaceWindow = NULL;
    if ( !CreateWindowSurface( &surfaceWindow, window ) ) {
        SDL_Quit();
        SDL_DestroyWindow( window );
        return EXIT_FAILURE;
    }


    Map map = MapCreate( "images/tileset.bmp" );

    Coord coord = {1, 1};
    Character character = CharacterCreate( "images/hero.bmp", coord );


    /* Boucle d'évènements */
    bool isOpen = true;
    bool mayUpdateScreen = false;
    bool firstTime = true;
    SDL_Event event;

    while ( isOpen ) {
        mayUpdateScreen = false;

        /* SDL_WaitEvent est bloquant */
        SDL_WaitEvent( &event );


        /* Si l'utilisateur décide de fermer la fenêtre */
        if ( event.window.event == SDL_WINDOWEVENT_CLOSE )
            isOpen = false;


        switch ( event.type ) {
        case SDL_KEYDOWN:
            switch ( event.key.keysym.sym ) {
            case SDLK_LEFT:
                CharacterMove( &character, LEFT );
                mayUpdateScreen = true;
                break;
            case SDLK_RIGHT:
                CharacterMove( &character, RIGHT );
                mayUpdateScreen = true;
                break;
            case SDLK_UP:
                CharacterMove( &character, UP );
                mayUpdateScreen = true;
                break;
            case SDLK_DOWN:
                CharacterMove( &character, DOWN );
                mayUpdateScreen = true;
                break;
            }
        }


        /* Mise à jour de la fenêtre */
        if ( mayUpdateScreen || firstTime ) {
            if ( firstTime )
                firstTime = false;

            MapDraw( &map, surfaceWindow );
            CharacterDraw( &character, surfaceWindow );

            SDL_UpdateWindowSurface( window );
        }
    }


    /* Nettoyage */
    MapFree( &map );
    CleanupSDL( window );


    /* Si on arrive jusqu'ici, c'est génial */
    return EXIT_SUCCESS;
}
