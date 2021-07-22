#include "entity_list.h"

EntityList *new_EntityList(SDL_Rect entity) {
    EntityList *entityList = malloc(sizeof(EntityList));
    if (entityList) {
        entityList->entity = entity;
        entityList->next = NULL;
        return entityList;
    }
    return NULL;
}

EntityList *EntityList_Append(EntityList *this, SDL_Rect entity) {
    EntityList **pEntityList = &this;
    while (*pEntityList)
        pEntityList = &(*pEntityList)->next;
    *pEntityList = new_EntityList(entity);
    if (*pEntityList)
        return this;
    else
        return NULL;
}

EntityList *EntityList_RemoveFirst(EntityList *this) {
    EntityList *EntityList = this;
    this = this->next;
    free(EntityList);
    return this;
}

EntityList *EntityList_Remove(EntityList *this, EntityList *entityList) {
    if (this == NULL)
        return NULL;

    EntityList *list = this, *temp = this, *prev;
    if (this == entityList) {
        list = this->next;
        free(entityList);
        return list;
    }

    prev = this;
    temp = this->next;
    while(temp != NULL && temp != entityList) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
        return list;

    prev->next = temp->next;
    free(temp);
    return list;
}

EntityList *delete_EntityList(EntityList *this) {
    while (this)
        this = EntityList_RemoveFirst(this);
    return this;
}