#include <vector>
#include <iostream>

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Box.H>

#include "block.h"
#include "game.h"

Game::Game(): Fl_Window(500, 500, 500, 500, "Sokoban") {
  resizable(this);
}

void Game::draw() {
  Fl_Window::draw();
  this->init_game();
  this->show_game();
  // this->show_menu();
}

// Game::~Game() {}

void Game::show_menu() {
  Fl_Color boxColor = fl_rgb_color(100, 200, 100);
  fl_draw_box(Fl_Boxtype::FL_FLAT_BOX,
    100,
    100, 50, 50, boxColor);
}

void Game::show_game() {
  int x = 0, y = 0;
  
  for (std::vector<Block> line: board_matrix) {
    for (Block cell: line) {
      fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, 50 * x, 50 * y, 50, 50, cell.getColor());
    
      x += 1;
    }
    x = 0;
    y += 1;
  }
}

void Game::init_game() {
  Fl_Color boxColor = fl_rgb_color(100, 200, 100);
  Fl_Color boxColor2 = fl_rgb_color(100, 100, 100);
  
  std::vector<Block> line1{Block(1, boxColor, Block::BlockType::wall),Block(1, boxColor, Block::BlockType::wall),Block(1, boxColor, Block::BlockType::wall)};
  std::vector<Block> line2{Block(1, boxColor, Block::BlockType::wall),Block(1, boxColor2, Block::BlockType::floor),Block(1, boxColor, Block::BlockType::wall)};
  std::vector<Block> line3{Block(1, boxColor, Block::BlockType::wall),Block(1, boxColor, Block::BlockType::wall),Block(1, boxColor, Block::BlockType::wall)};

  board_matrix.push_back(line1);
  board_matrix.push_back(line2);
  board_matrix.push_back(line3);
}