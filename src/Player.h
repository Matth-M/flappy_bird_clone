#pragma once
#include <SDL2/SDL_rect.h>
class Player {
public:
  Player(SDL_Rect &rect);
  Player(Player &&) = default;
  Player(const Player &) = default;
  Player &operator=(Player &&) = default;
  Player &operator=(const Player &) = default;
  ~Player();
  float vx, vy;
  void updatePos();
  void jump();
  SDL_Rect body;

private:
};
