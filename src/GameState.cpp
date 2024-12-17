#include "GameState.h"

GameState::GameState(bool state, bool spawn, Player &player, bool jump)
    : player(player), running(state), spawnEnvironment(spawn), jump(jump) {}

GameState::~GameState() {}
