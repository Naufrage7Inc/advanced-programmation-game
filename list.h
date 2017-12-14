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

bool  IsEmpty( TList list );
void* Head( TList list );
TList Rest( TList list );
TList CreateEmpty();
TList Create( void *ptr, TList list );
void  ModifyHead( void *ptr, TList list );
void  ModifyRest( TList a, TList b );
TList DeleteItem( TList item, TList list );
void  FreeList( TList list );

#endif // ifndef LISTE_H_INCLUDED
