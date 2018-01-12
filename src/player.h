#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED


#include <stdbool.h>
#include "list.h"


/* Structure pour stocker le résultat d'un joueur */
typedef struct {
	char* pseudo;
	int score;
} Player;


/* Enregistre le score du joueurs et affiche les meilleurs scores */
void saveScore(int score);


#endif
