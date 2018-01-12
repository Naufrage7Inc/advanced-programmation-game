#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED

#include <stdlib.h>
#include <stdbool.h>

struct TListElem {
    void             *ptr;
    struct TListElem *next;
};

typedef struct TListElem TListElem;

typedef TListElem       *TList;

/* Verifie si la liste est vide */
bool  IsEmpty( TList list );

/* Retourne le pointeur du premier élèment de la liste */
void* Head( TList list );

/* Retourne le reste des élèments de la liste sans le premier */
TList Rest( TList list );

/* Créer une liste vide */
TList CreateEmpty();

/* Créer une liste */
TList Create( void *ptr, TList list );

/* Permet de modifier la première valeur de la liste */
void  ModifyHead( void *ptr, TList list );

/* Permet de modifier le reste de la liste */
void  ModifyRest( TList a, TList b );

/* Permet de supprimer un élément de la liste */
TList DeleteItem( TList item, TList list );

/* Permet de libérer une liste */
void  FreeList( TList list );

#endif // ifndef LISTE_H_INCLUDED
