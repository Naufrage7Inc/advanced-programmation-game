#include "liste.h"

bool IsEmpty(TList list)
{
    if (list==CreateEmpty())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void* Head(TList list)
{
    return list->ptr;
}

TList Rest(TList list)
{
    return list->next;
}

TList CreateEmpty()
{
    return NULL;
}

TList Create(void *ptr,TList list)
{
    TListElem* temp = (TListElem*)malloc(sizeof(TListElem));
    temp->ptr = ptr;
    temp->next = list;
    return temp;
}

void ModifyHead(void *ptr, TList list)
{
    list->ptr=ptr;
}

void ModifyRest(TList a, TList b)
{
    a->next=b;

}

void FreeList(TList list)
{
    if (Rest(list)!= CreateEmpty())
    {
        FreeList(Rest(list));
        free(list);
    } else if (!IsEmpty(list)) {
        free(list);
    }
}
