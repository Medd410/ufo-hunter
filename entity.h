#ifndef UFO_HUNTER_ENTITY_H
#define UFO_HUNTER_ENTITY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Game Game;
typedef enum Entity_Direction Entity_Direction;

enum Entity_Direction {
    TOP, BOTTOM, LEFT, RIGHT
};

void Entity_SetRect(SDL_Rect *this, int x, int y, int w, int h);

void Entity_Draw(SDL_Rect *this, SDL_Renderer **renderer, SDL_Texture **texture);

void Entity_Move(SDL_Rect *this, Entity_Direction direction, int speed);

#endif //UFO_HUNTER_ENTITY_H
