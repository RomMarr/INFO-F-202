#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Box.H>

#include "game.h"

Game::Game(): Fl_Window(500, 500, 500, 500, "Sokoban") {
  resizable(this);
}

void Game::draw() {
    Fl_Window::draw();
    Game game;
    game.show_menu();
  }

// Game::~Game() {}

void Game::show_menu() {
  Fl_Color boxColor = fl_rgb_color(100, 200, 100);
  fl_draw_box(Fl_Boxtype::FL_FLAT_BOX,
    100,
    100, 50, 50, boxColor);
}