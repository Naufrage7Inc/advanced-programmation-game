#include "list.h"

/* Verifie si la liste est vide */
bool IsEmpty( TList list ) {
    if ( list == CreateEmpty() ) {
        return true;
    } else {
        return false;
    }
}

/* Retourne le pointeur du premier élèment de la liste */
void* Head( TList list ) {
    return list->ptr;
}

/* Retourne le reste des élèments de la liste sans le premier */
TList Rest( TList list ) {
    return list->next;
}

/* Créer une liste vide */
TList CreateEmpty() {
    return NULL;
}

/* Créer une liste */
TList Create( void *ptr, TList list ) {
    TListElem *temp = (TListElem *) malloc( sizeof( TListElem ) );

    temp->ptr = ptr;
    temp->next = list;
    return temp;
}

/* Permet de modifier la première valeur de la liste */
void ModifyHead( void *ptr, TList list ) {
    list->ptr = ptr;
}

/* Permet de modifier le reste de la liste */
void ModifyRest( TList a, TList b ) {
    a->next = b;
}

TList DeleteItem( TList item, TList list ) {
    if ( !IsEmpty( list ) ) {
        if ( list == item ) {
            TList temp = Rest( list );
            
            ModifyRest( list, CreateEmpty() );
            FreeList( list );

            return temp;
        } else {
            ModifyRest( list, DeleteItem( item, Rest( list ) ) );
        }
    } else {
        return list;
    }
}

/* Permet de libérer une liste */
void FreeList( TList list ) {
    if ( Rest( list ) != CreateEmpty() ) {
        FreeList( Rest( list ) );
        free( list );
    } else if ( !IsEmpty( list ) ) {
        free( list );
    }
}
