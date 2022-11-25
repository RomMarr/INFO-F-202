#include <memory>
#include <iostream>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

#include "game.hpp"
#include "model.hpp"
#include "view.hpp"
#include "controller.hpp"

using namespace std;

//int main(int argc, char *argv[]) {
  //Game game;
  //game.show(argc, argv);
  //return Fl::run();
//}



void levelEdit(){

}

int main(int argc, char *argv[]) {
  string level_file = "levels/1.txt";

  // Display_menus db_m;
  Game game;
  // db_m.display_homepage(); // affichage ecran d'accueil   
  // db_m.display_menu(); // affichage choix niveau ou modif niveau  -> dans le controller qui gere une fois clické sur un des choix -> modifie game.play !
  auto board = make_shared<Board>(level_file);  // ATTENTION A REMPLIR LA PARENTHESE !!!!!!!!!!!!!!!!!!!!!!!!!
  // if (game.getPlay()) game.game(board);
  // else game.edit_map();

  return 0;
}
