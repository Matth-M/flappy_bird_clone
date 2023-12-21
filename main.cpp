#include "GameState.h"
#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <stdio.h>
#include <stdlib.h>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

int main(int argc, char *argv[]) {
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

  // Set color for next operation
  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
  // Clear whole rendering target with previously selected color
  SDL_RenderClear(renderer);
  // Update screen
  SDL_RenderPresent(renderer);

  // Create player
  SDL_Rect player = SDL_Rect{.x = 0, .y = WINDOW_HEIGHT / 2, .w = 16, .h = 27};
  drawRectangle(renderer, player, 0xff, 0, 0);

  GameState state = GameState(true, false);
  while (state.running) {
    handleEvents(state);
    if (state.spawnEnvironment) {
      SDL_Rect env = SDL_Rect{
          .x = WINDOW_WIDTH / 2, .y = WINDOW_HEIGHT / 2, .w = 16, .h = 27};
      drawRectangle(renderer, env, 0xff, 0, 0x00);
    }
  }

  SDL_DestroyRenderer(renderer);
  // Destroy the window and shutdown the program
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
