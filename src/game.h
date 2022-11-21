#ifndef _GAME_H
#define _GAME_H

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Box.H>
#include <vector>

#include "block.h"

/**
class Game: public Fl_Window {
  std::vector<std::vector<Block>> board_matrix;
public:
  Game();
  void draw() override;
  void show_menu();
  void show_game();
  void init_game();
  // ~Game();
};
**/

class Game{
  bool play;  // true if play, false if edit_map
public:
  //Game(bool play);
  bool getPlay();
  void setPlay(bool new_play);
  void game(shared_ptr<Board> board);
  void edit_map();

};

#endif