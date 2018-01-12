#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "player.h"


/* Retourne et supprime le minimum d'une liste */
TList findAndDeleteMin(TList *input) {
    TList min = *input;    
    TList before = CreateEmpty();    
    TList temp = Rest(*input);
    
    /* Recherche du minimum */
    while ( !IsEmpty(temp) ) {
        Player *p = Head(temp), *pMin= Head(min);
        
        if ( p->score < pMin->score ) {
            before = min;
            min = temp;
        }

        temp = Rest(temp);
    }
    
    
    /* Destruction des liens */
    TList next = Rest(min);
    ModifyRest(min, CreateEmpty());
    
    if ( !IsEmpty(before) ) {
        ModifyRest(before, next);
    } else {
        *input = next;
    }
    
    return min;
}


/* Inverse l'ordre d'une liste */
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


/* Trie une liste dans l'ordre décroissant */
TList sort(TList input) {
    TList output = CreateEmpty();
    
    while ( !IsEmpty(input) ) {
        TList min = findAndDeleteMin(&input);
        ModifyRest(min, output);
        output = min;
    }
    
    return invert(output);
}


/* Enregistre le score du joueur et affiche les meilleurs scores */
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
	    /* Sauvegarde du score */
	    fseek(fHandle, 0, SEEK_END);
	    fprintf(fHandle, "%s %i\n", pseudo, score);
	    fseek(fHandle, 0, SEEK_SET);
	
	    /* Lecture du fichier */
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
	} else {
	    printf("Le fichier scores.txt n'existe pas ! Créez un fichier nommé score.txt dans le repertoire \"resources\".\n");
	}

	printf("\n--- TOP 5 ---\n");
	TList temp = listPlayers;
	int i = 0;
	while ( !IsEmpty(temp) && i < 5 ) {
		printf("   %s %i\n", ((Player*)Head(temp))->pseudo, ((Player*)Head(temp))->score);
		temp = Rest(temp);
		i++;
	}

	printf("\nVeuillez retourner sur la fenêtre de jeu pour continuer.\n");

	FreeList(listPlayers);
}

