#include "game.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <chrono>
#include <thread>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

void handleEvents(GameState &state) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
    case SDL_QUIT:
      state.running = false;
      break;
    case SDL_KEYDOWN:
      state.jump = true;
      break;
    default:
      break;
    }
  }
}

void drawRectangle(SDL_Renderer *renderer, const SDL_Rect &rect, Uint8 r,
                   Uint8 g, Uint8 b) {
  SDL_SetRenderDrawColor(renderer, r, g, b, 0);
  SDL_RenderFillRect(renderer, &rect);
  SDL_RenderPresent(renderer);
}

void gameLoop(GameState state, SDL_Renderer *renderer) {

  while (state.running) {

    std::this_thread::sleep_for(std::chrono::milliseconds(25));
    // Set color for next operation
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    // Clear whole rendering target with previously selected color
    SDL_RenderClear(renderer);
    // Update screen
    SDL_RenderPresent(renderer);
    handleEvents(state);
    drawRectangle(renderer, state.player.body, 0xff, 0, 0);
    state.player.updatePos();

    if (state.spawnEnvironment) {
      SDL_Rect env = SDL_Rect{
          .x = WINDOW_WIDTH / 2, .y = WINDOW_HEIGHT / 2, .w = 16, .h = 27};
      drawRectangle(renderer, env, 0xff, 0, 0x00);
    } else if (state.jump) {
      state.player.jump();
      state.jump = !state.jump;
    }
  }
}
