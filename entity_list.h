#ifndef UFO_HUNTER_ENTITY_LIST_H
#define UFO_HUNTER_ENTITY_LIST_H

#include "entity.h"

typedef struct EntityList EntityList;

struct EntityList {
    SDL_Rect entity;
    EntityList *next;
};

EntityList *new_EntityList(SDL_Rect entity);

EntityList *EntityList_Append(EntityList *this, SDL_Rect entity);

EntityList *EntityList_RemoveFirst(EntityList *this);

EntityList *EntityList_Remove(EntityList *this, EntityList *entityList);

EntityList *delete_EntityList(EntityList *entityList);

#endif //UFO_HUNTER_ENTITY_LIST_H
