#pragma once
#include "Entity.h"
#include "Player.h"
#include <vector>

class GameState {
public:
  bool running;
  bool spawnEnvironment;
  bool jump;
  bool end;
  Player player;
  std::vector<Entity> obstacles;
  GameState(bool running, bool spawnEnvironment, Player player, bool jump,
            bool end);
  GameState(GameState &&) = default;
  GameState(const GameState &) = default;
  void spawn_obstacle(int obstacle_speed);
  GameState &operator=(GameState &&) = default;
  GameState &operator=(const GameState &) = default;
  ~GameState();

private:
};
