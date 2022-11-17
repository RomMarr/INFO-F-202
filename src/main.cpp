#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

#include "game.h"

int main(int argc, char *argv[]) {
  Game game;
  game.show(argc, argv);
  return Fl::run();
}
