#include "stdio.h"
#include <iostream>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

#include "game.h"
#include "model.h"
#include "view.h"
#include "controller.h"
using namespace std;

//int main(int argc, char *argv[]) {
  //Game game;
  //game.show(argc, argv);
  //return Fl::run();
//}



void levelEdit(){

}

int main(int argc, char *argv[]) {
  Display_menus db_m;
  Game game;
  db_m.display_homepage(); // affichage ecran d'accueil   
  db_m.display_menu(); // affichage choix niveau ou modif niveau  -> dans le controller qui gere une fois clické sur un des choix -> modifie game.play !
  auto board = make_shared<Board>();  // ATTENTION A REMPLIR LA PARENTHESE !!!!!!!!!!!!!!!!!!!!!!!!!
  if (game.getPlay()) game.game(board);
  else game.edit_map();

  return 0;
}
