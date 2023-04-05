
#include "../headers/game.h"
#include "../headers/utils.h"
#include "../headers/obstacle.h"

void init_SDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur lors de l'initialisation de la SDL: %s\n", SDL_GetError());
        exit(1);
    }
}

SDL_Window *create_window(const char *title, int width, int height) {
    SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Erreur lors de la création de la fenêtre: %s\n", SDL_GetError());
        exit(1);
    }
    return window;
}

SDL_Renderer *create_renderer(SDL_Window *window) {
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Erreur lors de la création du renderer: %s\n", SDL_GetError());
        exit(1);
    }
    return renderer;
}

void handle_input(SDL_Event *event, int *running, Dino *dino, int *crouching, GameState *gameState) {
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT) {
            *running = 0;
        }
        handle_dino_input(dino, event, crouching);
        if (event->type == SDL_KEYDOWN) {
            if (*gameState == COLLISION && event->key.keysym.sym == SDLK_r) {
                *gameState = PLAYING;
                init_dino(dino);
                score = 0;
            }
        }
    }
}

void render_ground(SDL_Renderer *renderer) {
    SDL_Rect groundRect = {0, SCREEN_HEIGHT - GROUND_HEIGHT, SCREEN_WIDTH, GROUND_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderFillRect(renderer, &groundRect);
}

void cleanup(SDL_Window *window, SDL_Renderer *renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
