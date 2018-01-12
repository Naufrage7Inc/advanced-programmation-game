#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "player.h"


/* Il doit y avoir au moins un élément dans la liste */
TList findAndDeleteMin(TList *input) {
    TList min = *input;    
    TList before = CreateEmpty();    
    *input = Rest(*input);
    
    while ( !IsEmpty(*input) ) {
        Player *p = Head(*input), *pMin = Head(min);
        
        if ( p->score < pMin->score ) {
            before = min;
            min = *input;
        }

        *input = Rest(*input);
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


void sort(TList input, TList output) {
    output = Create(findAndDeleteMin(&input), CreateEmpty());
    printf("%i\n", ((Player*)Head(output))->score);
    
    /*TList temp = input;
    while (!IsEmpty(temp)) {
        printf("%d\n", ((Player*)Head(temp))->score);
        temp = Rest(temp);
    }*/
}

void saveScore(int score) {
	printf("Félicitations ! Vous avez attrapé tous les Pikachus sauvages !\n");
	printf("Votre score ( = nombre de pas ) est %i.\n", score);
	printf("Moins vous faites de pas, plus vous êtes efficace !\n");
	printf("\nSaisissez votre pseudo ( 10 caractères max. ) : ");

	char *pseudo = (char*)malloc(sizeof(char) * (10 + 1));
	scanf("%10s", pseudo);

	TList listPlayers = CreateEmpty();
	FILE *fHandle = fopen("resources/scores.txt", "r+");
	
	if ( fHandle != NULL ) {
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

        TList sorted = CreateEmpty();
        
        TList temp = listPlayers;
        while (!IsEmpty(temp)) {
            printf("%d\n", ((Player*)Head(temp))->score);
            temp = Rest(temp);
        }
        
        printf("---\n");
        
        
	    sort(listPlayers, sorted);
	}

	/*printf("\n--- TOP 5 ---\n");
	TList temp = listPlayers;
	while ( !IsEmpty(temp) ) {
		printf("   %s %i\n", ((Player*)Head(temp))->pseudo, ((Player*)Head(temp))->score);
		temp = Rest(temp);
	}

	printf("\n");
	printf("Veuillez retourner sur la fenêtre de jeu pour continuer.\n");

	FreeList(listPlayers);*/
}

