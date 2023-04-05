
#include "../headers/game.h"
#include "../headers/obstacle.h"

void init_obstacle(Obstacle *obstacle) {
    obstacle->x = 800;
    obstacle->y = SCREEN_HEIGHT - GROUND_HEIGHT - OBSTACLE_HEIGHT;
    obstacle->width = 50;
    obstacle->height = OBSTACLE_HEIGHT;
    obstacle->velX = -5;
}

void update_obstacle(Obstacle *obstacle, int score) {
    int speed_increase = score / 5000;
    obstacle->x += obstacle->velX - speed_increase;

    if (obstacle->x < -obstacle->width) {
        obstacle->x = 800;
        obstacle->y = (rand() % 2) ? SCREEN_HEIGHT - GROUND_HEIGHT - OBSTACLE_HEIGHT : SCREEN_HEIGHT - GROUND_HEIGHT - 2 * OBSTACLE_HEIGHT;
    }
}


void render_obstacle(Obstacle *obstacle, SDL_Renderer *renderer) {
    SDL_Rect rect = {obstacle->x, obstacle->y, obstacle->width, obstacle->height};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}