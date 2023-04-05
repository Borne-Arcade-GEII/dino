#ifndef DINO_H
#define DINO_H

#include <SDL.h>

typedef struct Dino {
    int x, y;
    int width, height;
    int velY;
    int ground_y;
    int jumping;
} Dino;

void init_dino(Dino *dino);
void handle_dino_input(Dino *dino, SDL_Event *event, int *crouching);
void update_dino(Dino *dino);
void render_dino(Dino *dino, SDL_Renderer *renderer);

#endif // DINO_H