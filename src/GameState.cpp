#include "GameState.h"

GameState::GameState(bool running, bool spawnEnvironment, Player &player, bool jump)
    : player(player), running(running), spawnEnvironment(spawnEnvironment), jump(jump) {}

GameState::~GameState() {}
