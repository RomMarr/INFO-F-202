#ifndef _ANIMATION_H
#define _ANIMATION_H

#include "point.hpp"

using namespace std;


class Animation {
private:    
  Point move;             // The move performed
  Point position_from; 
  Point animation_offset; // What will be animated, going from (-1, 0) to (0, 0)
  bool animated;
public:
  Animation();
  void setMove(Point new_move);
  void setPositionFrom(Point new_from);
  void setAnimationOffset(Point new_offset);
  void setAnimated(bool new_value);
  void animate(Point from, Point movement);          // Will initialize move, position_from, animation_offset and animated
  void computeAnimation();                           // Called on when redraw, will decrase the animation offset slowly
  Point getAnimatedPosition(Point current_position); // Return the animation_offset + current_position
  Point getMove();
  Point getPositionFrom();
  Point getAnimationOffset();
  bool isAnimated();
};

#endif