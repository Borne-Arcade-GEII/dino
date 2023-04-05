#include <SDL.h>
#include <SDL_ttf.h>
#include "../headers/game.h"
#include "../headers/dino.h"
#include "../headers/obstacle.h"
#include "../headers/utils.h"

int score = 0;

void run_game() {
    init_SDL();
    TTF_Init();

    SDL_Window *window = create_window("Chrome Dino", SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Renderer *renderer = create_renderer(window);

    Dino dino;
    init_dino(&dino);
    int crouching = 0;

    Obstacle obstacle;
    init_obstacle(&obstacle);

    TTF_Font *font = TTF_OpenFont("../fonts/font.ttf", 24);
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface *scoreSurface = NULL;
    SDL_Texture *scoreTexture = NULL;
    SDL_Rect scoreRect;

    SDL_Surface *digitSurfaces[10];
    SDL_Texture *digitTextures[10];

    for (int i = 0; i < 10; i++) {
        char digitText[2];
        sprintf(digitText, "%d", i);
        digitSurfaces[i] = TTF_RenderText_Solid(font, digitText, textColor);
        digitTextures[i] = SDL_CreateTextureFromSurface(renderer, digitSurfaces[i]);
    }

    SDL_Surface *restartSurface = NULL;
    SDL_Texture *restartTexture = NULL;
    SDL_Rect restartRect;

    restartSurface = TTF_RenderText_Solid(font, "Appuyez sur R pour recommencer", textColor);
    restartTexture = SDL_CreateTextureFromSurface(renderer, restartSurface);
    SDL_QueryTexture(restartTexture, NULL, NULL, &restartRect.w, &restartRect.h);
    restartRect.x = (SCREEN_WIDTH - restartRect.w) / 2;
    restartRect.y = (SCREEN_HEIGHT - restartRect.h) / 2;

    GameState gameState = PLAYING;
    int running = 1;

    SDL_Event event;


    while (running) {
        Uint32 startTime = SDL_GetTicks();

        handle_input(&event, &running, &dino, &crouching, &gameState);
        if (gameState == PLAYING) {
            update_dino(&dino);
            update_obstacle(&obstacle, score);
        }

        SDL_Rect dinoRect = {dino.x, dino.y, dino.width, dino.height};
        SDL_Rect obstacleRect = {obstacle.x, obstacle.y, obstacle.width, obstacle.height};

        if (check_collision(dinoRect, obstacleRect)) {
            gameState = COLLISION;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        render_ground(renderer);
        render_dino(&dino, renderer);
        render_obstacle(&obstacle, renderer);
        render_score(renderer, digitTextures, score, SCREEN_WIDTH - 7 * (20 + 5) - 10, 10);

        if (gameState == COLLISION) {
            SDL_RenderCopy(renderer, restartTexture, NULL, &restartRect);
            init_obstacle(&obstacle);
        }

        SDL_RenderPresent(renderer);

        SDL_DestroyTexture(scoreTexture);
        SDL_FreeSurface(scoreSurface);
        if(gameState== PLAYING) {
            score += SDL_GetTicks() - startTime;
        }

        SDL_Delay(1000 / 60);  // Limiter le taux de rafraîchissement à 60 FPS
    }

    for (int i = 0; i < 10; i++) {
        SDL_DestroyTexture(digitTextures[i]);
        SDL_FreeSurface(digitSurfaces[i]);
    }

    TTF_CloseFont(font);
    TTF_Quit();
    cleanup(window, renderer);
}

void render_score(SDL_Renderer *renderer, SDL_Texture **digitTextures, int score, int x, int y) {
    int numDigits = 7;
    int digitWidth = 20;
    int digitSpacing = 5;

    for (int i = numDigits - 1; i >= 0; i--) {
        int digit = score % 10;
        score /= 10;

        SDL_Rect srcRect = {0, 0, digitWidth, 24};
        SDL_Rect dstRect = {x + i * (digitWidth + digitSpacing), y, digitWidth, 24};
        SDL_RenderCopy(renderer, digitTextures[digit], &srcRect, &dstRect);
    }
}

int check_collision(SDL_Rect a, SDL_Rect b) {
    if (a.x + a.w <= b.x || b.x + b.w <= a.x || a.y + a.h <= b.y || b.y + b.h <= a.y) {
        return 0;
    }
    return 1;
}