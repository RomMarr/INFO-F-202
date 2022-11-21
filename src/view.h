#ifndef _VIEW_H
#define _VIEW_H

#include "model.h"
using namespace std;


// la vue en MVC : s'occupe d'afficher le board et les déplacements
// ATTENTION : Les classes de dessin de base qui appellent les fonctions fltk doivent être séparées de votre
//      code spécifique à Sokoban


class Display_menus{
public:
    void display_homepage();  // display the home page with both our names
    void display_menu();  
};

class Display_board{
    shared_ptr<Board> board;
public:
    Display_board(shared_ptr<Board> board);
    void display_board(Board board);  
    void display_move(Board board);  // display blocks moving
 }; 

#endif