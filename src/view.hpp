#ifndef _VIEW_H
#define _VIEW_H

#include "model.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>


// la vue en MVC : s'occupe d'afficher le board et les déplacements
// ATTENTION : Les classes de dessin de base qui appellent les fonctions fltk doivent être séparées de votre
//      code spécifique à Sokoban


// class Display_menus{
// public:
//     void display_homepage();  // display the home page with both our names
//     void display_menu();  
// };

// class Display_board{
//     shared_ptr<Board> board;
// public:
//     Display_board(shared_ptr<Board> board);
//     void display_board();  
//     void display_move();  // display blocks moving
//  }; 

class MainWindow: public Fl_Window {
    static constexpr inline double refreshPerSecond = 60;
    enum ScreenType { menu_screen, board_screen };
    shared_ptr<Board> board;
    ScreenType current_screen = menu_screen;
    void draw_board();
    void draw_menu();
public:
    MainWindow();
    void set_board(shared_ptr<Board> new_board);
    void draw() override;
    void display_menu();
    void display_board();
    static void timer_CB(void *userdata);
};

#endif