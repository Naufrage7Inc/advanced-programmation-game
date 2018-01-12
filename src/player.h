#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED


#include <stdbool.h>
#include "list.h"


/* Structure pour stocker le résultat d'un joueur */
typedef struct {
	char* pseudo;
	int score;
} Player;

/* Permet de chercher et de supprimer le minimum de la liste, il doit y avoir au moins un élément dans la liste */
TList findAndDeleteMin(TList *input);

/* Permet de retourner la liste inversé */
TList invert(TList input);

/* Permet de trier la liste de manière décroissante */
TList sort(TList list);

/* Permet de sauvegarder les scores dans la variable score */
void saveScore(int score);


#endif
