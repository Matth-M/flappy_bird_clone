#include "Entity.h"
#include "game.h"
#include <SDL2/SDL_rect.h>

const float MAX_X_ACCEL = 15;
const float MAX_Y_ACCEL = 15;

Entity::Entity(SDL_Rect &hitbox, float initial_vx, float initial_vy)
    : vx(initial_vx), vy(initial_vy), hitbox(hitbox) {}

Entity::~Entity() {}

void Entity::updatePos() {
  if (hitbox.y + vy >= WINDOW_HEIGHT - hitbox.h) {
    // Hits the bottom of the window
    hitbox.y = WINDOW_HEIGHT - hitbox.h;
    vy = 0;
  } else if (hitbox.y + vy <= 0) {
    hitbox.y = 0;
    vy = 0;
  } else {
    hitbox.y += vy;
  }
  if (hitbox.x + vx >= WINDOW_WIDTH) {
    hitbox.x = WINDOW_WIDTH;
    vx = 0;
  } else if (hitbox.x + vx <= 0) {
    hitbox.x = 0;
    vx = 0;
  } else {
    hitbox.x += vx;
  }
}

void Entity::updateAccel(float ax, float ay) {

  if (vx + ax > MAX_X_ACCEL) {
    vx = MAX_X_ACCEL;
  } else if (vx + ax < -MAX_X_ACCEL) {
    vx = -MAX_X_ACCEL;
  } else {
    vx = vx + ax;
  }

  if (vy + ay > MAX_Y_ACCEL) {
    vy = MAX_Y_ACCEL;
  } else if (vy + ay < -MAX_Y_ACCEL) {
    vy = -MAX_Y_ACCEL;
  } else {
    vy = vy + ay;
  }
}
