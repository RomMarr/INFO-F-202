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
  //init of board and controller
  shared_ptr<Board> board = make_shared<Board>(); 
  shared_ptr<Controller> controller = make_shared<Controller>(board);

  //init the view's classes
  MainMenu menu(controller);
  shared_ptr<MainWindow> window = make_shared<MainWindow>(menu);

  window->setController(controller);
  window->setBoard(board);

  window->show(argc, argv);

  return Fl::run();
}
