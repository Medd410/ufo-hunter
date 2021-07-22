#include "entity.h"

void Entity_SetRect(SDL_Rect *this, int x, int y, int w, int h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

void Entity_Draw(SDL_Rect *this, SDL_Renderer **renderer, SDL_Texture **texture) {
    if (this == NULL)
        return;
    SDL_RenderCopy(*renderer, *texture, NULL, this);
}

void Entity_Move(SDL_Rect *this, const Entity_Direction direction, const int speed) {
    if (this == NULL)
        return;
    int offset;
    int pos;
    switch (direction) {
        case TOP:
            this->y -= speed;
            break;
        case BOTTOM:
            this->y += speed;
            break;
        case LEFT:
            offset = this->x - speed;
            if (offset < 0) {
                this->x = 0;
            } else {
                this->x -= speed;
            }
            break;
        case RIGHT:
            offset = this->x + speed;
            pos = 512 - this->w;
            if (offset > pos) {
                this->x = pos;
            } else {
                this->x += speed;
            }
            break;
        default:
            break;
    }
}