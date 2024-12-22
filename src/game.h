#pragma once
#include "GameState.h"
#include <SDL2/SDL_render.h>
#include <vector>

const float GRAVITY = 1.25;
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

void drawRectangle(SDL_Renderer *renderer, const SDL_Rect &rect, Uint8 r,
                   Uint8 g, Uint8 b);
void handleEvents(GameState &state);
void gameLoop(GameState state, SDL_Renderer *renderer);
void spawn_obstacle(std::vector<Entity> &obstacles, int obstacle_speed);
