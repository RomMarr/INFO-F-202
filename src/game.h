#ifndef _GAME_H
#define _GAME_H

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Box.H>
#include <vector>

#include "bloc.h"

class Game: public Fl_Window {
  std::vector<std::vector<Bloc>> board_matrix;
public:
  Game();
  void draw() override;
  void show_menu();
  // ~Game();
};

#endif