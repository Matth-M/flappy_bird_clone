#pragma once
#include "Entity.h"

class Player {
public:
  Player(Entity body);
  Player(Player &&) = default;
  Player(const Player &) = default;
  Player &operator=(Player &&) = default;
  Player &operator=(const Player &) = default;
  ~Player();
  void jump();
  Entity body;

private:
};
