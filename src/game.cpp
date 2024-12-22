#include "game.h"
#include "Entity.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <algorithm>
#include <chrono>
#include <thread>
#include <vector>

// Handle keyboard events
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

  uint64_t cycle_iteration = 0;
  std::vector<Entity> obstacles;

  while (state.running) {

    // Pause the thread for a bit to make the game playable by humans
    std::this_thread::sleep_for(std::chrono::milliseconds(25));

    // Background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    handleEvents(state);

    // Remove obstacles past the player
    obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(),
                                   [](const Entity &obstacle) {
                                     return obstacle.hitbox.x <= 0;
                                   }),
                    obstacles.end());

    // Draw obstacles
    for (auto it = begin(obstacles); it != end(obstacles); ++it) {
      it->updatePos();
      drawRectangle(renderer, it->hitbox, 0xff, 0, 0);
    }

    if (cycle_iteration % 50 == 0) {
      const auto w = 5;
      const auto h = WINDOW_HEIGHT / 4;
      SDL_Rect obstacle_hitbox =
          SDL_Rect{.x = WINDOW_WIDTH - w, .y = 0, .w = w, .h = h};
      // Obstacles are moving towards the left
      auto obstacle_speed = -10;
      Entity obstacle = Entity(obstacle_hitbox, obstacle_speed, 0);
      obstacles.push_back(obstacle);
    }

    // Draw player
    drawRectangle(renderer, state.player.body.hitbox, 0, 0xff, 0);
    state.player.body.updatePos();
    state.player.body.updateAccel(0, GRAVITY);

    if (state.jump) {
      state.player.jump();
      state.jump = !state.jump;
    }
    cycle_iteration++;
  }
}
