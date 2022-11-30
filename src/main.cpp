#include "controller.hpp"
#include "view.hpp"
#include "model.hpp"

#include <tuple>
#include <memory>
#include <iostream>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

using namespace std;

int main(int argc, char *argv[]) {
  shared_ptr<Board> board = make_shared<Board>(); 
  shared_ptr<Controller> controller = make_shared<Controller>(board);

  MainMenu menu(controller);
  shared_ptr<MainWindow> window = make_shared<MainWindow>(menu);

  window->set_controller(controller);
  window->set_board(board);

  board->set_view(window);

  window->show(argc, argv);

  return Fl::run();
}
