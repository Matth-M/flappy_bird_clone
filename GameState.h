#pragma once

class GameState {
public:
  bool running;
  bool spawnEnvironment;
  GameState();
  GameState(bool state, bool spawn);
  GameState(GameState &&) = default;
  GameState(const GameState &) = default;
  GameState &operator=(GameState &&) = default;
  GameState &operator=(const GameState &) = default;
  ~GameState();

private:
};
