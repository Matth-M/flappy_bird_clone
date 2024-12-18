#pragma once
#include "Player.h"

class GameState {
public:
  bool running;
  bool spawnEnvironment;
  bool jump;
  Player &player;
  GameState(bool running, bool spawnEnvironment, Player &player, bool jump);
  GameState(GameState &&) = default;
  GameState(const GameState &) = default;
  GameState &operator=(GameState &&) = default;
  GameState &operator=(const GameState &) = default;
  ~GameState();

private:
};
