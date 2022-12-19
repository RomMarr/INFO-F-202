#include "animation.hpp"

#include "constants.hpp"
#include "point.hpp"

Animation::Animation(): animated{false} {}

void Animation::setMove(Point new_move) {
  move = new_move;
}

void Animation::setPositionFrom(Point new_from) {
  position_from = new_from;
}

void Animation::setAnimationOffset(Point new_offset) {
  animation_offset = new_offset;
}

void Animation::setAnimated(bool new_value) {
  animated = new_value;
}

void Animation::animate(Point from, Point movement) {
  setPositionFrom(from);
  setMove(movement);
  setAnimationOffset(movement * -1);
  setAnimated(true);
};

void Animation::computeAnimation() {
  if (isAnimated()) {
    Point new_animation;

    new_animation = getAnimationOffset() + (getMove() * (ANIMATION_SPEED / REFRESH_RATE));  // -1 -> -0.9 etc.

    if (getMove() == Point(1, 0) && new_animation.getPosX() >= 0 || 
        getMove() == Point(0, 1) && new_animation.getPosY() >= 0 || 
        getMove() == Point(-1, 0) && new_animation.getPosX() <= 0 || 
        getMove() == Point(0, -1) && new_animation.getPosY() <= 0
    ) {
      setAnimated(false);
      setAnimationOffset({0, 0});
    }

    if (isAnimated()) {
      setAnimationOffset(new_animation);
    }
  }
}

Point Animation::getAnimatedPosition(Point current_position) {
  return current_position + getAnimationOffset();
}

Point Animation::getMove() {
  return move;
}

Point Animation::getPositionFrom() {
  return position_from;
}

Point Animation::getAnimationOffset() {
  return animation_offset;
}

bool Animation::isAnimated() {
  return animated;
}