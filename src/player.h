#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED


#include <stdbool.h>
#include "list.h"


/* Structure pour stocker le résultat d'un joueur */
typedef struct {
	char* pseudo;
	int score;
} Player;


TList sort(TList list);
void saveScore(int score);


#endif
