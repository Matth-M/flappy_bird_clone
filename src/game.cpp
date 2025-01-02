#include "game.h"
#include "Entity.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <iostream>
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
    case SDL_KEYDOWN: {

      if (e.key.keysym.sym == SDLK_ESCAPE) {
        state.running = false;

      } else {
        state.jump = true;
      }
      break;
    }
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

  // Spacing distance between 2 spawned objects
  const auto obstacle_spacing = 300;

  auto obstacle_speed = -8;
  auto last_spawned_object_position = 0;
  uint64_t distance_traveled = 0;
  auto last_checkpoint_position = 0;
  const auto checkpoint_spacing = WINDOW_WIDTH * 3;
  while (state.running) {

    // Pause the thread for a bit to make the game playable by humans
    std::this_thread::sleep_for(std::chrono::milliseconds(25));

    // Background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    handleEvents(state);

    // Remove obstacles past the player
    state.obstacles.erase(std::remove_if(state.obstacles.begin(), state.obstacles.end(),
                                   [](const Entity &obstacle) {
                                     return obstacle.hitbox.x <= 0;
                                   }),
                    state.obstacles.end());

    // Draw obstacles and update their speed
    for (size_t i = 0; i < state.obstacles.size(); ++i) {
      state.obstacles[i].updatePos();
      state.obstacles[i].vx = obstacle_speed;
      drawRectangle(renderer, state.obstacles[i].hitbox, 0xff, 0, 0);
      if (state.player.collides(state.obstacles[i])) {
        state.end = true;
      }
    }

    if ((distance_traveled - last_checkpoint_position) >= checkpoint_spacing) {
      // Obstacles are moving towards the left
      obstacle_speed -= 2;
      last_checkpoint_position = distance_traveled;
      std::cout << "Faster !" << "\n";
    }
    distance_traveled += abs(obstacle_speed);

    if ((distance_traveled - last_spawned_object_position) >=
        obstacle_spacing) {
      state.spawn_obstacle(obstacle_speed);
      last_spawned_object_position = distance_traveled;
    }

    // Draw player and update its position
    drawRectangle(renderer, state.player.body.hitbox, 0, 0xff, 0);
    state.player.body.updatePos();
    state.player.body.updateAccel(0, GRAVITY);

    if (state.jump) {
      state.player.jump();
      state.jump = !state.jump;
    }

    if (state.end) {
      std::cout << "You lost" << "\n";
      std::cout << "Distance traveled: " << distance_traveled << " pixels"
                << "\n";
      break;
    }
  }
}
