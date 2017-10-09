#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <SDL2/SDL.h>

#include "constants.h"
#include "engine.h"
#include "character.h"
#include "map.h"


int main() {
    srand( time( NULL ) );


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
        CleanupSDL( window );
        return EXIT_FAILURE;
    }


    /* Création de la carte et du personnage */
    Map* map = MapCreate( "images/ground.bmp", "map.bin" );
    Character* sacha = CharacterCreate( "images/sacha.bmp", CoordCreate( 1, 1 ) );
    Character* pikachu = CharacterCreate( "images/pikachu.bmp", CoordCreate( 2, 2 ) );


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


        /* Déplacement du personnage */
        if ( event.type == SDL_KEYDOWN ) {
            SDL_Keycode key = event.key.keysym.sym;
            if ( key == SDLK_LEFT ) {
                CharacterMove( sacha, LEFT );
                mayUpdateScreen = true;
            }
            else if ( key == SDLK_RIGHT ) {
                CharacterMove( sacha, RIGHT );
                mayUpdateScreen = true;
            } else if ( key == SDLK_UP ) {
                CharacterMove( sacha, UP );
                mayUpdateScreen = true;
            } else if ( key == SDLK_DOWN ) {
                CharacterMove( sacha, DOWN );
                mayUpdateScreen = true;
            }
        }


        /* Mise à jour de la fenêtre */
        if ( mayUpdateScreen || firstTime ) {
            if ( firstTime )
                firstTime = false;


            MapDraw( map, surfaceWindow );
            CharacterDraw( sacha, surfaceWindow );
            CharacterDraw( pikachu, surfaceWindow );

            SDL_UpdateWindowSurface( window );
        }
    }


    /* Nettoyage */
    CharacterFree( sacha );
    CharacterFree( pikachu );
    MapFree( map );

    MapFree( map );
    CleanupSDL( window );


    /* Si on arrive jusqu'ici, c'est génial */
    return EXIT_SUCCESS;
}
