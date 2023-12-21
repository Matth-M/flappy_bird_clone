#pragma once
#include "GameState.h"
#include <SDL2/SDL_render.h>

void drawRectangle(SDL_Renderer *renderer, const SDL_Rect &rect, Uint8 r,
                   Uint8 g, Uint8 b);
void handleEvents(GameState &state);
