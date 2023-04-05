#ifndef GAME_H
#define GAME_H

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define GROUND_HEIGHT 50
#define OBSTACLE_HEIGHT 50

#include <SDL.h>

typedef enum { PLAYING, PAUSED, COLLISION } GameState;

void run_game();
void render_score(SDL_Renderer *renderer, SDL_Texture **digitTextures, int score, int x, int y);
int check_collision(SDL_Rect a, SDL_Rect b);

extern int score;

#endif // GAME_H