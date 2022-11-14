#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Box.H>

#include "game.h"

Game::Game() {}

// Game::~Game() {}

void Game::show_menu() {
  Fl_Color boxColor = fl_rgb_color(100, 200, 100);
  fl_draw_box(Fl_Boxtype::FL_FLAT_BOX,
    100,
    100, 50, 50, boxColor);
}