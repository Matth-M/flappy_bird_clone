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
    case SDL_KEYDOWN:
      state.jump = true;
      break;
    default:
      break;
    }
  }
}

enum OBSTACLE_TYPE { Gate_High, Gate_Low, Falling, Rising, last };

void drawRectangle(SDL_Renderer *renderer, const SDL_Rect &rect, Uint8 r,
                   Uint8 g, Uint8 b) {
  SDL_SetRenderDrawColor(renderer, r, g, b, 0);
  SDL_RenderFillRect(renderer, &rect);
  SDL_RenderPresent(renderer);
}

void spawn_obstacle(std::vector<Entity> &obstacles, int obstacle_speed) {
  auto obstacle_type = static_cast<OBSTACLE_TYPE>(rand() % last);
  const auto w = 15;
  switch (obstacle_type) {
  case OBSTACLE_TYPE::Rising: {
    const auto h = 3*WINDOW_HEIGHT / 5;
    SDL_Rect obstacle_hitbox =
        SDL_Rect{.x = WINDOW_WIDTH - w, .y = WINDOW_HEIGHT - h, .w = w, .h = h};
    Entity obstacle = Entity(obstacle_hitbox, obstacle_speed, 0);
    obstacles.push_back(obstacle);
    break;
  }
  case OBSTACLE_TYPE::Falling: {
    const auto h = 3 * WINDOW_HEIGHT / 5;
    SDL_Rect obstacle_hitbox =
        SDL_Rect{.x = WINDOW_WIDTH - w, .y = 0, .w = w, .h = h};
    Entity obstacle = Entity(obstacle_hitbox, obstacle_speed, 0);
    obstacles.push_back(obstacle);
    break;
  }
  case OBSTACLE_TYPE::Gate_High: {
    const auto h_top = WINDOW_HEIGHT / 4;
    SDL_Rect obstacle_top_hitbox =
        SDL_Rect{.x = WINDOW_WIDTH - w, .y = 0, .w = w, .h = h_top};
    Entity obstacle_top = Entity(obstacle_top_hitbox, obstacle_speed, 0);

    const auto h_bot = WINDOW_HEIGHT / 2;
    SDL_Rect obstacle_bot_hitbox = SDL_Rect{
        .x = WINDOW_WIDTH - w, .y = WINDOW_HEIGHT - h_bot, .w = w, .h = h_bot};
    Entity obstacle_bot = Entity(obstacle_bot_hitbox, obstacle_speed, 0);
    obstacles.push_back(obstacle_top);
    obstacles.push_back(obstacle_bot);
    break;
  }
  case OBSTACLE_TYPE::Gate_Low: {
    const auto h_top = WINDOW_HEIGHT / 2;
    SDL_Rect obstacle_top_hitbox =
        SDL_Rect{.x = WINDOW_WIDTH - w, .y = 0, .w = w, .h = h_top};
    Entity obstacle_top = Entity(obstacle_top_hitbox, obstacle_speed, 0);

    const auto h_bot = WINDOW_HEIGHT / 4;
    SDL_Rect obstacle_bot_hitbox = SDL_Rect{
        .x = WINDOW_WIDTH - w, .y = WINDOW_HEIGHT - h_bot, .w = w, .h = h_bot};
    Entity obstacle_bot = Entity(obstacle_bot_hitbox, obstacle_speed, 0);
    obstacles.push_back(obstacle_top);
    obstacles.push_back(obstacle_bot);
    break;
  }
  default:
    break;
  }
}

void gameLoop(GameState state, SDL_Renderer *renderer) {

  uint64_t cycle_iteration = 0;
  std::vector<Entity> obstacles;
  uint64_t distance_traveled = 0;

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
    for (size_t i = 0; i < obstacles.size(); ++i) {
      obstacles[i].updatePos();
      drawRectangle(renderer, obstacles[i].hitbox, 0xff, 0, 0);
      if (state.player.collides(obstacles[i])) {
        state.end = true;
      }
    }

    // Obstacles are moving towards the left
    auto obstacle_speed = -10;
    distance_traveled += abs(obstacle_speed);

    const auto obstacle_spacing = 25;
    // Spawn new obstable
    if (cycle_iteration % obstacle_spacing == 0) {
      spawn_obstacle(obstacles, obstacle_speed);
    }
    // Draw player
    drawRectangle(renderer, state.player.body.hitbox, 0, 0xff, 0);
    state.player.body.updatePos();
    state.player.body.updateAccel(0, GRAVITY);

    if (state.jump) {
      state.player.jump();
      state.jump = !state.jump;
    }

    if (state.end) {
      std::cout << "You lost" << "\n";
      std::cout << "Distance traveled: " << distance_traveled << " pixels" << "\n";
      break;
    }
    cycle_iteration++;
  }
}
