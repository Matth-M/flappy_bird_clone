#include "GameState.h"

GameState::GameState(bool state, bool spawn, Player &player, bool jump)
    : player(player) {
  this->running = state;
  this->spawnEnvironment = spawn;
  this->player = player;
  this->jump = jump;
}

GameState::~GameState() {}
