#pragma once
#include <SDL2/SDL_rect.h>
class Entity {
public:
  Entity(SDL_Rect &hitbox, float initial_vx, float initial_vy);
  Entity(Entity &&) = default;
  Entity(const Entity &) = default;
  Entity &operator=(Entity &&) = default;
  Entity &operator=(const Entity &) = default;
  ~Entity();
  float vx, vy;
  void updatePos();
  void updateAccel(float ax, float ay);
  SDL_Rect hitbox;

private:
};
