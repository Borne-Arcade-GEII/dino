#ifndef UTILS_H
#define UTILS_H

#include <SDL.h>
#include "dino.h"

void init_SDL();
SDL_Window *create_window(const char *title, int width, int height);
SDL_Renderer *create_renderer(SDL_Window *window);
void handle_input(SDL_Event *event, int *running, Dino *dino, int *crouching, GameState *gameState);
void render_ground(SDL_Renderer *renderer);
void cleanup(SDL_Window *window, SDL_Renderer *renderer);

#endif // UTILS_H