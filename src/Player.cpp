#include "Player.h"
#include <iostream>
const float JUMP_STRENGTH = 11;
Player::Player(Entity body) : body(body) {}

Player::~Player() {}
void Player::jump() {
  if (body.vy > 0)
    body.vy = -2;
  body.updateAccel(0, -JUMP_STRENGTH);
}

bool Player::collides(const Entity &obstacle) const {
  const auto obstacle_x = obstacle.hitbox.x;
  const auto obstacle_w = obstacle.hitbox.w;
  const auto obstacle_y = obstacle.hitbox.y;
  const auto obstacle_h = obstacle.hitbox.h;

  const auto x = body.hitbox.x;
  const auto w = body.hitbox.w;
  const auto y = body.hitbox.y;
  const auto h = body.hitbox.h;

  if (obstacle_y - h <= y && y <= obstacle_y + obstacle_h &&
      (obstacle_x - w <= x && x <= obstacle_x + obstacle_w)) {
    return true;
  }
  return false;
}
