#include "Player.h"
const float JUMP_STRENGTH = 15;
Player::Player(Entity body) : body(body) {}

Player::~Player() {}
void Player::jump() { this->body.updateAccel(0, -JUMP_STRENGTH); }
