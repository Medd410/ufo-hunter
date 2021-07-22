#ifndef UFO_HUNTER_GAME_H
#define UFO_HUNTER_GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "entity.h"
#include "entity_list.h"

struct Game {
    //
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *textureBackground;
    SDL_Texture *textureSpaceship;
    SDL_Texture *textureUfo;
    SDL_Texture *textureBullet;
    SDL_Texture *textureScore;
    TTF_Font *font;
    SDL_Event event;
    int score;
    int elapsedFrames;
    int lastshootFrame;
    int lastspawnFrame;
    // ENTITIES
    SDL_Rect spaceship;
    EntityList *bullets;
    EntityList *ufos;
};

Game *new_Game();

void Game_LoadTextures(Game *this);

int Game_HandleEvents(Game *this);

void Game_UpdateScore(Game *this, int amount);

void Game_DrawScore(Game *this);

void Game_CheckCollision(Game *this);

void Game_UpdateBullets(Game *this);

void Game_UpdateUfos(Game *this);

void Game_Update(Game *this);

void Game_DrawBullets(Game *this);

void Game_DrawUfos(Game *this);

void Game_Render(Game *this);

void delete_Game(Game *this);

#endif //UFO_HUNTER_GAME_H
