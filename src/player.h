#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED


#include <stdbool.h>
#include "list.h"


/* Structure pour stocker le résultat d'un joueur */
typedef struct {
	char* pseudo;
	int score;
} Player;


void sort(TList list, TList sorted);
void saveScore(int score);


#endif
