#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL.h>

typedef struct Obstacle {
    int x, y;
    int width, height;
    int velX;
} Obstacle;

void init_obstacle(Obstacle *obstacle);
void update_obstacle(Obstacle *obstacle, int score);
void render_obstacle(Obstacle *obstacle, SDL_Renderer *renderer);

#endif // OBSTACLE_H