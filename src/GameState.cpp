#include "GameState.h"
#include "Player.h"
#include "game.h"

Player init_player() {
  // Create player
  SDL_Rect player_hitbox = SDL_Rect{
      .x = PLAYER_STARTING_X, .y = WINDOW_HEIGHT / 2, .w = 15, .h = 30};
  Entity player_body = Entity(player_hitbox, 0, 0);
  Player player = Player(player_body);
  return player;
}

GameState::GameState() : player(init_player()) {
  jump = false;
  end = false;
  distance_traveled = 0;
  spawnEnvironment = 0;
  obstacle_speed = INITIAL_OBSTACLE_SPEED;
  running = true;
  obstacles = std::vector<Entity>();
  last_spawned_object_position = 0;
  last_checkpoint_position = 0;
}
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
