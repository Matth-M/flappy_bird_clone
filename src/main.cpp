#include "Entity.h"
#include "GameState.h"
#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <stdio.h>
#include <stdlib.h>

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

  auto state = GameState();
  gameLoop(state, renderer);

  SDL_DestroyRenderer(renderer);
  // Destroy the window and shutdown the program
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
