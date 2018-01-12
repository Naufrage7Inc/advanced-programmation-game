#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "player.h"


/* Permet de chercher et de supprimer le minimum de la liste, il doit y avoir au moins un élément dans la liste */
TList findAndDeleteMin(TList *input) {
    TList min = *input;
    TList before = CreateEmpty();
    TList temp = Rest(*input);

    while ( !IsEmpty(temp) ) {
        Player *p = Head(temp), *pMin= Head(min);

        if ( p->score < pMin->score ) {
            before = min;
            min = temp;
        }

        temp = Rest(temp);
    }

    TList next = Rest(min);
    ModifyRest(min, CreateEmpty());

    if ( !IsEmpty(before) ) {
        ModifyRest(before, next);
    } else {
        *input = next;
    }

    return min;
}

/* Permet de retourne la liste inversé */
TList invert(TList input) {
    TList temp = input;
    TList output = CreateEmpty();

    while ( !IsEmpty(temp) ) {
        output = Create(Head(temp), output);
        temp = Rest(temp);
    }

    FreeList(input);

    return output;
}

/* Permet de trier la liste de manière décroissante */
TList sort(TList input) {
    TList output = CreateEmpty();

    while ( !IsEmpty(input) ) {
        TList min = findAndDeleteMin(&input);
        ModifyRest(min, output);
        output = min;
    }

    return invert(output);
}

/* Permet de sauvegarder les scores dans la variable score */
void saveScore(int score) {
    system("clear");

	printf("Félicitations ! Vous avez attrapé tous les Pikachus sauvages !\n");
	printf("Votre score ( = nombre de pas ) est %i.\n", score);
	printf("Moins vous faites de pas, plus vous êtes efficace !\n");
	printf("\nSaisissez votre pseudo ( 10 caractères max. ) : ");

	char *pseudo = (char*)malloc(sizeof(char) * (10 + 1));
	scanf("%10s", pseudo);

	TList listPlayers = CreateEmpty();
	FILE *fHandle = fopen("resources/scores.txt", "r+");

	if ( fHandle != NULL ) {
	    fseek(fHandle, 0, SEEK_END);
	    fprintf(fHandle, "%s %i\n", pseudo, score);
	    fseek(fHandle, 0, SEEK_SET);

	    int ret = 2;
	    while ( ret == 2 ) {
	        Player *p = (Player*)malloc(sizeof(Player));
            p->pseudo = (char*)malloc(sizeof(char) * 11);

	        ret = fscanf(fHandle, "%s %i", p->pseudo, &(p->score));

	        if ( ret == 2 )
	            listPlayers = Create(p, listPlayers);
	        else
	            free(p);
	    }

	    fclose(fHandle);

	    listPlayers = sort(listPlayers);
	}

	printf("\n--- TOP 5 ---\n");
	TList temp = listPlayers;
	int i = 0;
	while ( !IsEmpty(temp) && i < 5 ) {
		printf("   %s %i\n", ((Player*)Head(temp))->pseudo, ((Player*)Head(temp))->score);
		temp = Rest(temp);
		i++;
	}

	printf("\n");
	printf("Veuillez retourner sur la fenêtre de jeu pour continuer.\n");
	
	temp = listPlayers;
	while ( !IsEmpty(temp) ) {
	    free(((Player*)Head(temp))->pseudo);
	    free(Head(temp));
	    temp = Rest(temp);
	}

	FreeList(listPlayers);
	
	free(pseudo);
}

