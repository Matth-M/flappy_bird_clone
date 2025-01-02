#include "Entity.h"
#include "GameState.h"
#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

GameState init_state() {
  // Create player
  SDL_Rect player_hitbox =
      SDL_Rect{.x = PLAYER_STARTING_X, .y = WINDOW_HEIGHT / 2, .w = 15, .h = 30};
  Entity player_body = Entity(player_hitbox, 0, 0);
  Player player = Player(player_body);

  GameState state = GameState(true, false, player, false, false);
  return state;
}

int main() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("SDL could not initialize: Error %s\n", SDL_GetError());
    return 1;
  }

  // SDL Window setup
  SDL_Window *window =
      SDL_CreateWindow("SDL2 Tutorial", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

  if (window == NULL) {
    printf("Unable to create window. Error %s\n", SDL_GetError());
    return 1;
  }

  // Create renderer
  SDL_Renderer *renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_SOFTWARE);
  if (renderer == NULL) {
    printf("Unable to create renderer. Error %s\n", SDL_GetError());
    return 1;
  }

  auto state = init_state();
  gameLoop(state, renderer);

  SDL_DestroyRenderer(renderer);
  // Destroy the window and shutdown the program
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
