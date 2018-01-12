/* Suivi de la mémoire avec Visual Studio */
#ifdef _MSC_VER 
#define _CRTDBG_MAP_ALLOC
#endif


/* Pour utiliser les fonctions _s ( sécurisées ) du C, à commenter si erreur de compilation */
//#define USE_SECURE


/* En-têtes standards */
#include <stdlib.h>
#ifdef _MSC_VER 
#include <crtdbg.h>
#endif
#include <stdio.h>
#include <stdbool.h>
#include <time.h>


/* En-têtes SDL2 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>


/* En-têtes du projet */
#include "constants.h"
#include "engine.h"
#include "character.h"
#include "map.h"
#include "list.h"
#include "player.h"


/*
* L'idée ici est de créer une fenêtre avec un fond et une ambiance musicale
* Comme il n'y a pas de boutons en SDL, on simule les boutons avec du texte
*/
bool displayMenu(SDL_Window* window, SDL_Surface* surfaceWindow) {
    /* Variables de contrôle */
    bool isOpen = true;
    bool play = false;


    /* Création du fond du menu */
    SDL_Surface *surfaceMenu = LoadBMP("resources/images/menu.bmp");


    /* Chargement de la police en taille 90 */
    TTF_Font* font = TTF_OpenFont("resources/fonts/font.ttf", 90);
    SDL_Color colorWhite = { 255, 255, 255 };
    SDL_Color colorRed = { 255, 100, 100 };


    /* Création d'un texte en taille 90 */
    SDL_Surface* textTitle = TTF_RenderText_Blended(font, "Pika Chasse", colorWhite);


    /* Fermeture puis réouverture de la police en taille 65 */
    TTF_CloseFont(font);
    font = TTF_OpenFont("resources/fonts/font.ttf", 65);


    /* Création de textes en taille 65 */
    SDL_Surface* textPlay = TTF_RenderText_Blended(font, "JOUER", colorWhite);
    SDL_Surface* textQuit = TTF_RenderText_Blended(font, "QUITTER", colorWhite);


    /* Création des positions des textes */
    SDL_Rect positionTextTitle = { WINDOW_WIDTH / 2 - textTitle->w / 2, WINDOW_HEIGHT / 2 - textTitle->h / 2 - 150, 0, 0 };
    SDL_Rect positionTextPlay = { WINDOW_WIDTH / 2 - textPlay->w / 2, WINDOW_HEIGHT / 2 - textPlay->h / 2 + 75, 0, 0 };
    SDL_Rect positionTextQuit = { WINDOW_WIDTH / 2 - textQuit->w / 2, WINDOW_HEIGHT / 2 - textQuit->h / 2 + 165, 0, 0 };


    /* Affichage des textes ( une fois uniquement ) */
    SDL_BlitSurface(surfaceMenu, NULL, surfaceWindow, NULL);
    SDL_BlitSurface(textTitle, NULL, surfaceWindow, &positionTextTitle);
    SDL_BlitSurface(textPlay, NULL, surfaceWindow, &positionTextPlay);
    SDL_BlitSurface(textQuit, NULL, surfaceWindow, &positionTextQuit);

    SDL_UpdateWindowSurface(window);


    /* Lecture de la musique */
    Mix_Music *music = Mix_LoadMUS("resources/sounds/menu.wav");
    Mix_PlayMusic(music, -1);


    /* Boucle de contrôle pour les boutons ( textes ) */
    while (isOpen) {
        /* SDL_WaitEvent est bloquant */
        SDL_Event event;
        SDL_WaitEvent(&event);


        /* Si le joueur décide de fermer la fenêtre */
        if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
            isOpen = false;
        }


        /* Si le joueur clique */
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            /* Position du clic*/
            int x = event.motion.x;
            int y = event.motion.y;


            /* S'il clique sur le bouton "JOUER" */
            if (x >= positionTextPlay.x && x <= positionTextPlay.x + textPlay->w && y >= positionTextPlay.y && y <= positionTextPlay.y + textPlay->h) {
                isOpen = false;
                play = true;
            }
            /* S'il clique sur le bouton "QUITTER" */
            else if (x >= positionTextQuit.x && x <= positionTextQuit.x + textQuit->w && y >= positionTextQuit.y && y <= positionTextQuit.y + textQuit->h) {
                isOpen = false;
                play = false;
            }
        }
        else if (event.type == SDL_MOUSEMOTION) {
            /* Position du clic*/
            int x = event.motion.x;
            int y = event.motion.y;


            /* Gestion de l'animation du texte ( = survol de la souris ) */
            if (x >= positionTextPlay.x && x <= positionTextPlay.x + textPlay->w && y >= positionTextPlay.y && y <= positionTextPlay.y + textPlay->h) {
                SDL_FreeSurface(textPlay);
                textPlay = TTF_RenderText_Blended(font, "JOUER", colorRed);
            }
            else {
                SDL_FreeSurface(textPlay);
                textPlay = TTF_RenderText_Blended(font, "JOUER", colorWhite);
            }


            /* Gestion de l'animation du texte ( = survol de la souris ) */
            if (x >= positionTextQuit.x && x <= positionTextQuit.x + textQuit->w && y >= positionTextQuit.y && y <= positionTextQuit.y + textQuit->h) {
                SDL_FreeSurface(textQuit);
                textQuit = TTF_RenderText_Blended(font, "QUITTER", colorRed);
            }
            else {
                SDL_FreeSurface(textQuit);
                textQuit = TTF_RenderText_Blended(font, "QUITTER", colorWhite);
            }
        }


        /* Mise à jour des surfaces qui changent */
        SDL_BlitSurface(textPlay, NULL, surfaceWindow, &positionTextPlay);
        SDL_BlitSurface(textQuit, NULL, surfaceWindow, &positionTextQuit);

        SDL_UpdateWindowSurface(window);
    }


    /* Nettoyage */
    TTF_CloseFont(font);

    SDL_FreeSurface(surfaceMenu);
    SDL_FreeSurface(textPlay);
    SDL_FreeSurface(textQuit);

    Mix_HaltMusic();
    Mix_FreeMusic(music);


    return play;
}

/*
* L'idée ici est de créer la fenêtre de jeu ( avec les différents personnages )
* et de gérer toute la mécanique ( déplacement, ... )
*/
int playGame(SDL_Window* window, SDL_Surface* surfaceWindow) {
    /* Création de la carte et du personnage */
    Map *map = MapCreate("resources/images/ground.bmp");
    Character *sacha = CharacterCreate("resources/images/sacha.bmp", CoordCreate(rand() % N_BLOCKS_X, rand() % N_BLOCKS_Y));
    TList pikachus = CreateEmpty();


    /* Chargement et lecture de la musique d'ambiance */
    Mix_Music *music = Mix_LoadMUS("resources/sounds/sound.wav");
    Mix_PlayMusic(music, -1);


    /* Chargement des bruitages */
    Mix_Chunk  *pika1 = Mix_LoadWAV("resources/sounds/pika_1.wav");
    Mix_Chunk  *pika2 = Mix_LoadWAV("resources/sounds/pika_2.wav");


    /* Créations des pikachus dans la liste */
    for (int i = 0; i < N_PIKACHU; i++) {
        /* Créatio d'un pikachu dans la liste */
        Character *character = CharacterCreate("resources/images/pikachu.bmp", CoordCreate(0, 0));
        pikachus = Create(character, pikachus);


        /* Tant que le pikachu créé est sur une position déjà occupée */
        do {
            int x = rand() % N_BLOCKS_X;
            int y = rand() % N_BLOCKS_Y;
            CharacterSetCoord(character, CoordCreate(x, y));
        } while (IsThereCharacterAtPosition(CharacterGetCoord(character), sacha, Rest(pikachus)));
    }


    /* Variables de contrôle */
    SDL_Event event;

    bool isOpen = true;
    bool keyDown = false;
    bool firstTime = true;
    bool mayUpdateScreen = true;

    int steps = 0;


    /* Boucle de contrôle */
    while (isOpen) {
        /* Rien n'a changé depuis le dernier affichage */
        mayUpdateScreen = false;


        /* SDL_PollEvent est non bloquant */
        while (SDL_PollEvent(&event)) {
            /* Si l'utilisateur décide de fermer la fenêtre */
            if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                isOpen = false;
                steps = -1;
            }


            /* Déplacement du personnage */
            const Uint8 *keystate = SDL_GetKeyboardState(NULL);


            /* Déplacement vers la gauche */
            if (keystate[SDL_SCANCODE_LEFT] && !keyDown) {
                CharacterMove(sacha, LEFT);
                mayUpdateScreen = true;
                keyDown = true;
                ++steps;
                /* Déplacement vers la droite */
            }
            else if (keystate[SDL_SCANCODE_RIGHT] && !keyDown) {
                CharacterMove(sacha, RIGHT);
                mayUpdateScreen = true;
                keyDown = true;
                ++steps;
                /* Déplacement vers le haut */
            }
            else if (keystate[SDL_SCANCODE_UP] && !keyDown) {
                CharacterMove(sacha, UP);
                mayUpdateScreen = true;
                keyDown = true;
                ++steps;
                /* Déplacement vers le bas */
            }
            else if (keystate[SDL_SCANCODE_DOWN] && !keyDown) {
                CharacterMove(sacha, DOWN);
                mayUpdateScreen = true;
                keyDown = true;
                ++steps;
                /* Détecte si la touche est relâchée ( évite la répétition des touches ) */
            }
            else if (!keystate[SDL_SCANCODE_LEFT] &&
                !keystate[SDL_SCANCODE_RIGHT] &&
                !keystate[SDL_SCANCODE_UP] &&
                !keystate[SDL_SCANCODE_DOWN]) {
                keyDown = false;
            }
        }


        /* Suppression d'un pikachu si le joueur en capture un */
        TList temp = pikachus;
        while (!IsEmpty(temp)) {
            /* Récupération d'un pikachu */
            Character* character = (Character*)Head(temp);


            /* Si le joueur est sur un pikachu */
            if (CharacterGetCoord(character).x == CharacterGetCoord(sacha).x &&
                CharacterGetCoord(character).y == CharacterGetCoord(sacha).y) {
                /* Suppression du pikachu de la liste */
                pikachus = DeleteItem(temp, pikachus);


                /* Libération du pikachu*/
                CharacterFree(character);


                /* Permet de quitter la boucle */
                temp = CreateEmpty();


                /* Lecture d'un bruitage */
                if (rand() % 2 == 0) {
                    Mix_PlayChannel(1, pika1, 0);
                }
                else {
                    Mix_PlayChannel(1, pika2, 0);
                }
            }
            /* Sinon on continue le parcours de la liste*/
            else {
                temp = Rest(temp);
            }
        }


        /* Si le joueur a capturé tous les pikachus, on ferme la fenêtre pour passer
           à la fenêtre de score */
        if (IsEmpty(pikachus)) {
            isOpen = false;
        }

        /* Mise à jour de la fenêtre */
        if (mayUpdateScreen || firstTime) {
            firstTime = false;

            /* Déplacemet des pikachus ( puisque le joueur s'est aussi déplacé ) */
            temp = pikachus;

            while (!IsEmpty(temp)) {
                /* ... */
                Character* character = (Character*)Head(temp);


                /* On choisi une direction au hasard */
                int direction = rand() % 4;
                Coord coord;

                /* Dans chaque cas, on regarde s'il n'y a pas de pikachus ou le joueur sur la case où
                   on va déplacer le pikachu */
                switch (direction) {
                case LEFT:
                    coord = CharacterGetCoord(character);
                    coord.x--;
                    if (!IsThereCharacterAtPosition(coord, sacha, pikachus)) {
                        CharacterMove(character, LEFT);
                    }
                    break;

                case RIGHT:
                    coord = CharacterGetCoord(character);
                    coord.x++;
                    if (!IsThereCharacterAtPosition(coord, sacha, pikachus)) {
                        CharacterMove(character, RIGHT);
                    }
                    break;

                case UP:
                    coord = CharacterGetCoord(character);
                    coord.y--;
                    if (!IsThereCharacterAtPosition(coord, sacha, pikachus)) {
                        CharacterMove(character, UP);
                    }
                    break;

                case DOWN:
                    coord = CharacterGetCoord(character);
                    coord.y++;
                    if (!IsThereCharacterAtPosition(coord, sacha, pikachus)) {
                        CharacterMove(character, DOWN);
                    }
                    break;
                }


                /* On continue le parcours de la liste*/
                temp = Rest(temp);
            }


            /* Affichage de la carte et du joueur */
            MapDraw(map, surfaceWindow);
            CharacterDraw(sacha, surfaceWindow);


            /* Affichage des pikachus */
            TList temp = pikachus;

            while (!IsEmpty(temp)) {
                Character *character = (Character*)Head(temp);
                CharacterDraw(character, surfaceWindow);
                temp = Rest(temp);
            }


            /* Mise à jour de la fenêtre */
            SDL_UpdateWindowSurface(window);
        }
    }


    /* Au moment où l'on capture un pikachu, celui-ci émet un cri. On attend qu'il
       finisse de "crier" avec une boucle */
    while (Mix_Playing(1)) {
        /* On ne fait rien ... On consomme pas mal en CPU mais bon, c'est de
        courte durée ( même pas 1 sec ). C'est quelque chose à améliorer */
    }


    /* Nettoyage */
    CharacterFree(sacha);
    MapFree(map);

    while (!IsEmpty(pikachus)) {
        Character *character = (Character*)Head(pikachus);
        CharacterFree(character);
        TList temp = Rest(pikachus);
        ModifyRest(pikachus, CreateEmpty());
        FreeList(pikachus);
        pikachus = temp;
    }

    Mix_HaltMusic();

    Mix_FreeMusic(music);
    Mix_FreeChunk(pika1);
    Mix_FreeChunk(pika2);

    return steps;
}


/*
* L'idée ici est d'afficher une fenêtre avec le score du joueur, un bouton ( = texte ) pour
* se rendre au menu et une option pour quitter directement
*/
bool displayScore(SDL_Window* window, SDL_Surface* surfaceWindow, int steps) {
    /* Variables de contrôle */
    bool isOpen = true;
    bool play = false;

    SDL_Event event;


    /* Création du fond */
    SDL_Surface *surfaceMenu = LoadBMP("resources/images/menu.bmp");


    /* Chargement de la police en taille 90 + création de la couleur blanc */
    TTF_Font* font = TTF_OpenFont("resources/fonts/font.ttf", 90);
    SDL_Color colorWhite = { 255, 255, 255 };
    SDL_Color colorRed = { 255, 100, 100 };


    /* Création du texte avec le score en taille 90 */
    char score[128];
#ifdef USE_SECURE
    sprintf_s(score, 128, "Score %i", steps);
#else
    sprintf(score, "Score %i", steps);
#endif
    SDL_Surface* textScore = TTF_RenderText_Blended(font, score, colorWhite);


	/* Message demandant à l'utilisateur d'aller sur la console pour saisir son score */
    TTF_CloseFont(font);
    font = TTF_OpenFont("resources/fonts/font.ttf", 25);
    SDL_Surface* textConsole = TTF_RenderText_Blended(font, "Veuillez retournez sur la console !", colorWhite);


	/* Fermeture et chargement de la police en taille 65 */
    TTF_CloseFont(font);
    font = TTF_OpenFont("resources/fonts/font.ttf", 65);


    /* Création des textes en taille 65 */
    SDL_Surface* textAgain = TTF_RenderText_Blended(font, "MENU", colorWhite);
    SDL_Surface* textQuit = TTF_RenderText_Blended(font, "QUITTER", colorWhite);


    /* Création des positions pour les textes */
    SDL_Rect positionTextScore = { WINDOW_WIDTH / 2 - textScore->w / 2, WINDOW_HEIGHT / 2 - textScore->h / 2 - 150, 0, 0 };
    SDL_Rect positionTextAgain = { WINDOW_WIDTH / 2 - textAgain->w / 2, WINDOW_HEIGHT / 2 - textAgain->h / 2 + 75, 0, 0 };
    SDL_Rect positionTextQuit = { WINDOW_WIDTH / 2 - textQuit->w / 2, WINDOW_HEIGHT / 2 - textQuit->h / 2 + 165, 0, 0 };
	SDL_Rect positionTextConsole = { WINDOW_WIDTH / 2 - textConsole->w / 2, WINDOW_HEIGHT / 2 - textScore->h / 2, 0, 0 };


    /* Affichage à l'écran */
    SDL_BlitSurface(surfaceMenu, NULL, surfaceWindow, NULL);
    SDL_BlitSurface(textScore, NULL, surfaceWindow, &positionTextScore);
    SDL_BlitSurface(textAgain, NULL, surfaceWindow, &positionTextAgain);
    SDL_BlitSurface(textQuit, NULL, surfaceWindow, &positionTextQuit);
	SDL_BlitSurface(textConsole, NULL, surfaceWindow, &positionTextConsole);

    SDL_UpdateWindowSurface(window);


	saveScore(steps);


    /* Boucle de contrôle */
    while (isOpen) {
        /* SDL_WaitEvent est bloquant */
        SDL_WaitEvent(&event);


        /* Si le joueur ferme la fenêtre */
        if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
            isOpen = false;
        }


        /* Gestion des boutons ( = texte ) */
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            /* Position de la souris */
            int x = event.motion.x;
            int y = event.motion.y;


            /* Le joueur clique sur le menu pour aller au menu */
            if (x >= positionTextAgain.x && x <= positionTextAgain.x + textAgain->w && y >= positionTextAgain.y && y <= positionTextAgain.y + textAgain->h) {
                isOpen = false;
                play = true;
                /* Le joueur clique sur le menu pour quitter */
            }
            else if (x >= positionTextQuit.x && x <= positionTextQuit.x + textQuit->w && y >= positionTextQuit.y && y <= positionTextQuit.y + textQuit->h) {
                isOpen = false;
                play = false;
            }
        }
        else if (event.type == SDL_MOUSEMOTION) {
            /* Position du clic*/
            int x = event.motion.x;
            int y = event.motion.y;


            /* Gestion de l'animation du texte ( = survol de la souris ) */
            if (x >= positionTextAgain.x && x <= positionTextAgain.x + textAgain->w && y >= positionTextAgain.y && y <= positionTextAgain.y + textAgain->h) {
                SDL_FreeSurface(textAgain);
                textAgain = TTF_RenderText_Blended(font, "MENU", colorRed);
            }
            else {
                SDL_FreeSurface(textAgain);
                textAgain = TTF_RenderText_Blended(font, "MENU", colorWhite);
            }


            /* Gestion de l'animation du texte ( = survol de la souris ) */
            if (x >= positionTextQuit.x && x <= positionTextQuit.x + textQuit->w && y >= positionTextQuit.y && y <= positionTextQuit.y + textQuit->h) {
                SDL_FreeSurface(textQuit);
                textQuit = TTF_RenderText_Blended(font, "QUITTER", colorRed);
            }
            else {
                SDL_FreeSurface(textQuit);
                textQuit = TTF_RenderText_Blended(font, "QUITTER", colorWhite);
            }
        }


        /* Mise à jour des surfaces qui changent */
        SDL_BlitSurface(surfaceMenu, NULL, surfaceWindow, NULL);
		SDL_BlitSurface(textScore, NULL, surfaceWindow, &positionTextScore);
		SDL_BlitSurface(textAgain, NULL, surfaceWindow, &positionTextAgain);
		SDL_BlitSurface(textQuit, NULL, surfaceWindow, &positionTextQuit);

        SDL_UpdateWindowSurface(window);
    }


    /* Nettoyage */
    TTF_CloseFont(font);
    SDL_FreeSurface(surfaceMenu);
    SDL_FreeSurface(textScore);
    SDL_FreeSurface(textAgain);
    SDL_FreeSurface(textQuit);
	SDL_FreeSurface(textConsole);


    return play;
}

int main(int argc, char *argv[]) {
#ifdef _MSC_VER 
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif


    /* Initialisation du temps */
    srand((unsigned int)time(NULL));


    /* Initialisation de la SDL */
    if (!InitSDL()) {
        exit(EXIT_FAILURE);
    }

    /* Initialisatio de SDL_TTF */
    if (TTF_Init() == -1) {
        exit(EXIT_FAILURE);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
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


    /* Allocation des cannaux audio */
    Mix_AllocateChannels(2);
    Mix_Volume(0, MIX_MAX_VOLUME);


    /* Boucle de jeu */
    bool play = true;

    while (play) {
        /* On affiche le menu*/
        if (displayMenu(window, surfaceWindow)) {
            /* Le joueur joue, à la fin on récupère son score */
            int steps = playGame(window, surfaceWindow);

            if (steps >= 0) {
                if (!displayScore(window, surfaceWindow, steps)) {
                    play = false;
                }
            }
        }
        else {
            play = false;
        }
    }


    /* Nettoyage */
    Mix_CloseAudio();
    TTF_Quit();

    CleanupSDL(window); // Détruit la fenêtre + SDL_Quit


    /* Si on arrive jusqu'ici, c'est génial */
    return EXIT_SUCCESS;
}
