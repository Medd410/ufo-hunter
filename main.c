#include "game.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));
    Game *game = new_Game();
    if (game == NULL)
        return EXIT_FAILURE;

    Game_LoadTextures(game);
    Uint32 frameDelay = 16, frameStart, frameTime;

    while (1) {
        frameStart = SDL_GetTicks();
        if (Game_HandleEvents(game) == 0)
            break;
        Game_Update(game);
        Game_Render(game);
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }

    return EXIT_SUCCESS;
}