#include "GameState.h"

GameState::GameState(bool running, bool spawnEnvironment, Player &player,
                     bool jump, bool end)
    : running(running), spawnEnvironment(spawnEnvironment), jump(jump),
      end(end), player(player) {}

GameState::~GameState() {}
