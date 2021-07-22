#include "game.h"

Game *new_Game() {
    Game *game = NULL;
    for (;;) {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
            break;
        }

        game = malloc(sizeof(Game));
        if (game == NULL)
            break;

        game->window = NULL;
        game->renderer = NULL;

        game->window = SDL_CreateWindow("UFO Hunter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        512, 512, 0);
        if (game->window == NULL) {
            fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
            break;
        }

        game->renderer = SDL_CreateRenderer(game->window, -1, 0);
        if (game->renderer == NULL) {
            fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
            break;
        }

        TTF_Init();

        game->textureBackground = NULL;
        game->textureSpaceship = NULL;
        game->textureUfo = NULL;
        game->textureBullet = NULL;
        game->textureScore = NULL;
        game->font = TTF_OpenFont("Arial.ttf", 20);
        game->elapsedFrames = 0;
        game->lastshootFrame = 0;
        game->lastspawnFrame = 0;
        game->score = 0;
        Entity_SetRect(&game->spaceship, 240, 480, 32, 32);
        game->bullets = NULL;
        game->ufos = NULL;

        return game;
    }
    delete_Game(game);
    return NULL;
}

void Game_LoadTextures(Game *this) {
    IMG_Init(0);
    SDL_Surface *surface = IMG_Load("background.jpg");
    this->textureBackground = SDL_CreateTextureFromSurface(this->renderer, surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("spaceship.png");
    this->textureSpaceship = SDL_CreateTextureFromSurface(this->renderer, surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("bullet.png");
    this->textureBullet = SDL_CreateTextureFromSurface(this->renderer, surface);
    SDL_FreeSurface(surface);
    surface = IMG_Load("ufo.png");
    this->textureUfo = SDL_CreateTextureFromSurface(this->renderer, surface);
    SDL_FreeSurface(surface);
    IMG_Quit();
}

int Game_HandleEvents(Game *this) {
    SDL_PollEvent(&this->event);
    if (this->event.type == SDL_QUIT)
        return 0;
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    if (keyState[SDL_SCANCODE_SPACE]) {
        if (this->elapsedFrames - this->lastshootFrame > 15) {
            this->lastshootFrame = this->elapsedFrames;
            SDL_Rect bullet = {this->spaceship.x + 15, this->spaceship.y - 10, 2, 12};
            this->bullets = EntityList_Append(this->bullets, bullet);
        }
    }
    if (keyState[SDL_SCANCODE_RIGHT]) {
        Entity_Move(&this->spaceship, RIGHT, 4);
    }
    if (keyState[SDL_SCANCODE_LEFT]) {
        Entity_Move(&this->spaceship, LEFT, 4);
    }
    return 1;
}

void Game_UpdateScore(Game *this, int amount) {
    this->score += amount;
    if (this->score < 0)
        this->score = 0;
}

void Game_CheckCollision(Game *this) {
    for (EntityList *bulletList = this->bullets; bulletList != NULL; bulletList = bulletList->next) {
        for (EntityList *ufoList = this->ufos; ufoList != NULL; ufoList = ufoList->next) {
            if (SDL_HasIntersection(&bulletList->entity, &ufoList->entity)) {
                Game_UpdateScore(this, 10);
                this->bullets = EntityList_Remove(this->bullets, bulletList);
                this->ufos = EntityList_Remove(this->ufos, ufoList);
            }
        }
    }
}

void Game_UpdateBullets(Game *this) {
    for (EntityList *bulletList = this->bullets; bulletList != NULL; bulletList = bulletList->next) {
        Entity_Move(&bulletList->entity, TOP, 6);
        if (bulletList->entity.y < 0) {
            this->bullets = EntityList_Remove(this->bullets, bulletList);
        }
    }
}

void Game_UpdateUfos(Game *this) {
    for (EntityList *ufoList = this->ufos; ufoList != NULL; ufoList = ufoList->next) {
        Entity_Move(&ufoList->entity, BOTTOM, 2);
        if (ufoList->entity.y > 512) {
            Game_UpdateScore(this, -50);
            this->ufos = EntityList_Remove(this->ufos, ufoList);
        }
    }
}

void Game_Update(Game *this) {
    this->elapsedFrames++;
    if (this->elapsedFrames - this->lastspawnFrame > 45) {
        this->lastspawnFrame = this->elapsedFrames;
        SDL_Rect ufo = {rand() % 481, -32, 32, 32};
        this->ufos = EntityList_Append(this->ufos, ufo);
    }
    Game_CheckCollision(this);
    Game_UpdateBullets(this);
    Game_UpdateUfos(this);
}

void Game_DrawBullets(Game *this) {
    for (EntityList *bulletList = this->bullets; bulletList != NULL; bulletList = bulletList->next) {
        Entity_Draw(&bulletList->entity, &this->renderer, &this->textureBullet);
    }
}

void Game_DrawUfos(Game *this) {
    for (EntityList *ufoList = this->ufos; ufoList != NULL; ufoList = ufoList->next) {
        Entity_Draw(&ufoList->entity, &this->renderer, &this->textureUfo);
    }
}

void Game_DrawScore(Game *this ) {
    SDL_Color color = {255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(this->font, "Score : 0000", color);
    this->textureScore = SDL_CreateTextureFromSurface(this->renderer, surface);
    SDL_FreeSurface(surface);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(this->textureScore, NULL, NULL, &texW, &texH);
    SDL_Rect rect = {0, 0, texW, texH};
    SDL_RenderCopy(this->renderer, this->textureScore, NULL, &rect);
}

void Game_Render(Game *this) {
    SDL_RenderClear(this->renderer);
    SDL_RenderCopy(this->renderer, this->textureBackground, NULL, NULL);
    Entity_Draw(&this->spaceship, &this->renderer, &this->textureSpaceship);
    Game_DrawBullets(this);
    Game_DrawUfos(this);
    Game_DrawScore(this);
    SDL_RenderPresent(this->renderer);
}

void delete_Game(Game *this) {
    if (this->renderer != NULL)
        SDL_DestroyRenderer(this->renderer);
    if (this->window != NULL)
        SDL_DestroyWindow(this->window);
    SDL_Quit();
    free(this);
}