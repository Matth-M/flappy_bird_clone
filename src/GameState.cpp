#include "GameState.h"

GameState::GameState(bool running, bool spawnEnvironment, Player &player,
                     bool jump)
    : running(running), spawnEnvironment(spawnEnvironment), jump(jump),
      player(player) {}

GameState::~GameState() {}
