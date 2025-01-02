#pragma once
#include "GameState.h"
#include <SDL2/SDL_render.h>
#include <vector>

const float GRAVITY = 1.45;
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const auto PLAYER_STARTING_X = 30;

// _ used for random genration
enum OBSTACLE_TYPE { Gate_High, Gate_Low, Falling, Rising, _ };

void drawRectangle(SDL_Renderer *renderer, const SDL_Rect &rect, Uint8 r,
                   Uint8 g, Uint8 b);
void handleEvents(GameState &state);
void gameLoop(GameState state, SDL_Renderer *renderer);
void spawn_obstacle(std::vector<Entity> &obstacles, int obstacle_speed);
