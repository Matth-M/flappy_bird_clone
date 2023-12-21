#include "GameState.h"

GameState::GameState(){};
GameState::GameState(bool state, bool spawn) {
  this->running = state;
  this->spawnEnvironment = spawn;
}

GameState::~GameState() {}
