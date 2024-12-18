#include "Player.h"
#include <SDL2/SDL_rect.h>
const float JUMP_STRENGTH = 15;

Player::Player(SDL_Rect &rect) { this->body = rect; }

Player::~Player() {}

void Player::updatePos() {
  // increasing y means going downwards on the screen
  this->vy += GRAVITY;
  this->body.y += this->vy;
  this->body.x += this->vx;
}

void Player::jump() { this->vy = -JUMP_STRENGTH; }
