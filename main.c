#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <SDL2/SDL.h>

#include "constants.h"
#include "engine.h"
#include "character.h"
#include "map.h"
#include "liste.h"


int n_malloc;
int n_free;

int main() {
    n_malloc = 0;
    n_free   = 0;


    /* Initialisation du temps */
    srand(time(NULL));


    /* Initialisation de la SDL */
    if (!InitSDL()) {
        exit(EXIT_FAILURE);
    }


    /* Création de la fenêtre */
    SDL_Window *window = NULL;

    if (!CreateWindow(&window, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE)) {
        SDL_Quit();
        exit(EXIT_FAILURE);
    }


    /* Création de la surface de la fenêtre */
    SDL_Surface *surfaceWindow = NULL;

    if (!CreateWindowSurface(&surfaceWindow, window)) {
        CleanupSDL(window);
        exit(EXIT_FAILURE);
    }


    /* Création de la carte et du personnage */
    Map *map         = MapCreate("images/ground.bmp");
    Character *sacha = CharacterCreate("images/sacha.bmp",
                                       CoordCreate(rand() % N_BLOCKS_X,
                                                   rand() % N_BLOCKS_Y));
    TList pikachu = CreateEmpty();


    for (int i = 0; i < N_PIKACHU; i++) {
        pikachu = Create(CharacterCreate("images/pikachu.bmp", CoordCreate(0, 0)),
                         pikachu);
        Character *character = Head(pikachu);

        do {
            CharacterSetCoord(character,
                              CoordCreate(rand() % N_BLOCKS_X,
                                          rand() % N_BLOCKS_Y));
        }
        while (IsThereCharacterAtPosition(CharacterGetCoord(character), sacha,
                                          pikachu, i - 1));
    }


    /* Boucle d'évènements */
    bool isOpen          = true;
    bool keyDown         = false;
    bool firstTime       = true;
    bool mayUpdateScreen = true;

    while (isOpen) {
        mayUpdateScreen = false;


        /* SDL_PollEvent est non bloquant */
        SDL_Event event;
        SDL_PollEvent(&event);


        /* Si l'utilisateur décide de fermer la fenêtre */
        if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
            isOpen = false;
        }


        /* Déplacement du personnage */
        const Uint8 *keystate = SDL_GetKeyboardState(NULL);

        if (keystate[SDL_SCANCODE_LEFT] && !keyDown) {
            CharacterMove(sacha, LEFT);
            mayUpdateScreen = true;
            keyDown         = true;
        } else if (keystate[SDL_SCANCODE_RIGHT] && !keyDown) {
            CharacterMove(sacha, RIGHT);
            mayUpdateScreen = true;
            keyDown         = true;
        } else if (keystate[SDL_SCANCODE_UP] && !keyDown) {
            CharacterMove(sacha, UP);
            mayUpdateScreen = true;
            keyDown         = true;
        } else if (keystate[SDL_SCANCODE_DOWN] && !keyDown) {
            CharacterMove(sacha, DOWN);
            mayUpdateScreen = true;
            keyDown         = true;
        } else if (!keystate[SDL_SCANCODE_LEFT] &&
                   !keystate[SDL_SCANCODE_RIGHT] && !keystate[SDL_SCANCODE_UP] &&
                   !keystate[SDL_SCANCODE_DOWN]) {
            keyDown = false;
        }


        /* Mise à jour de la fenêtre */
        if (mayUpdateScreen || firstTime) {
            firstTime = false;

            MapDraw(map, surfaceWindow);
            CharacterDraw(sacha, surfaceWindow);

            TList temp = pikachu;

            while (!IsEmpty(temp))
            {
                Character *character = Head(temp);
                CharacterDraw(character, surfaceWindow);
                temp = Rest(temp);
            }

            SDL_UpdateWindowSurface(window);
        }
    }


    /* Nettoyage */
    CharacterFree(sacha);

    TList temp = pikachu;

    while (!IsEmpty(temp))
    {
        Character *character = Head(temp);
        CharacterFree(character);
        temp = Rest(temp);
    }

    MapFree(map);

    FreeList(pikachu);

    CleanupSDL(window);
    SDL_Quit();


    printf("n_malloc = %i\n", n_malloc);
    printf("n_free   = %i\n", n_free);


    /* Si on arrive jusqu'ici, c'est génial */
    return EXIT_SUCCESS;
}
