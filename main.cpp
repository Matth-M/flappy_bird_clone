#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("SDL could not initialize: Error %s\n", SDL_GetError());
    return 1;
  }

  // SDL Window setup
  SDL_Window *window =
      SDL_CreateWindow("SDL2 Tutorial", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

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
  SDL_Rect player = SDL_Rect{.x = 0, .y = 0, .w = 16, .h = 27};
  // Red player
  SDL_SetRenderDrawColor(renderer, 0xff, 0, 0, 0);
  SDL_RenderFillRect(renderer, &player);
  SDL_RenderPresent(renderer);

  SDL_Event e;
  bool running = true;
  while (running) {
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_QUIT:
        running = false;
        break;
      default:
        break;
      }
    }
  }

  SDL_DestroyRenderer(renderer);
  // Destroy the window and shutdown the program
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
