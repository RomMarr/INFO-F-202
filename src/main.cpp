#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

#include "game.h"

class MainWindow: public Fl_Window {
 public:
  MainWindow(): Fl_Window(500, 500, 500, 500, "Projet") {
    resizable(this);
  }
  void draw() override {
    Fl_Window::draw();
    Game game;
    game.show_menu();
  }
};

int main(int argc, char *argv[]) {
  MainWindow window;
  window.show(argc, argv);
  return Fl::run();
}
