#include "../headers/game.h"
#include "../headers/dino.h"

void init_dino(Dino *dino) {
    dino->x = 50;
    dino->width = 50;
    dino->height = 100;
    dino->ground_y = SCREEN_HEIGHT - GROUND_HEIGHT - dino->height;
    dino->y = dino->ground_y;
    dino->velY = 0;
    dino->jumping = 0;
}

void handle_dino_input(Dino *dino, SDL_Event *event, int *crouching) {
    if (event->type == SDL_KEYDOWN) {
        if (!dino->jumping && (event->key.keysym.sym == SDLK_SPACE || event->key.keysym.sym == SDLK_z || event->key.keysym.sym == SDLK_UP)) {
            dino->jumping = 1;
            dino->velY = -20;
        }
        if (!*crouching && !dino->jumping && (event->key.keysym.sym == SDLK_DOWN || event->key.keysym.sym == SDLK_s)) {
            *crouching = 1;
            dino->height = 50;
            dino->y += 50;
        }
        if (dino->jumping && (event->key.keysym.sym == SDLK_DOWN || event->key.keysym.sym == SDLK_s)) {
            dino->velY += 10; // Ajoutez cette ligne pour accélérer la chute
        }
    } else if (event->type == SDL_KEYUP) {
        if (*crouching && (event->key.keysym.sym == SDLK_DOWN || event->key.keysym.sym == SDLK_s)) {
            *crouching = 0;
            dino->height = 100;
            dino->y -= 50;
        }
    }
}


void update_dino(Dino *dino) {
    if (dino->jumping) {
        dino->y += dino->velY;
        dino->velY += 1;

        if (dino->y >= dino->ground_y) {
            dino->y = dino->ground_y;
            dino->jumping = 0;
        }
    }
}

void render_dino(Dino *dino, SDL_Renderer *renderer) {
    SDL_Rect rect = {dino->x, dino->y, dino->width, dino->height};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}


