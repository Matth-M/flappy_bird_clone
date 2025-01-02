#include "GameState.h"
#include "game.h"
#include <iostream>

GameState::GameState(bool running, bool spawnEnvironment, Player player,
                     bool jump, bool end)
    : running(running), spawnEnvironment(spawnEnvironment), jump(jump),
      end(end), player(player) {
  obstacles = std::vector<Entity>();
}

GameState::~GameState() {}

// Add an obstacle to the list of obstacles
void GameState::spawn_obstacle(int obstacle_speed) {
  // Generate an obstacle type randomly
  auto obstacle_type = static_cast<OBSTACLE_TYPE>(rand() % OBSTACLE_TYPE::_);
  const auto w = 15;
  switch (obstacle_type) {
  case OBSTACLE_TYPE::Rising: {
    const auto h = 3 * WINDOW_HEIGHT / 5;
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
