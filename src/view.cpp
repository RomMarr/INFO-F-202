#include "view.hpp"

#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>

// void Display_menus::display_homepage(){

// }; 


// void Display_menus::display_menu(){

// };  


// Display_board::Display_board(shared_ptr<Board> board): board{board}{};


// void Display_board::display_board(){
    
// };  


// void Display_board::display_move(){

// };

// class MainWindow: public Fl_Window {
//     shared_ptr<Board> board;
// public:
//     void set_board(shared_ptr board);
//     void display_menu();
//     void display_board();
// }

MainWindow::MainWindow(): Fl_Window(500, 500, 500, 500, "Sokoban") {
    Fl::add_timeout(1.0/refreshPerSecond, timer_CB, this);
    resizable(this);
}

void MainWindow::draw_board() {
    for (size_t y = 0; y < (*board).get_height(); y++) {
        for (size_t x = 0; x < (*board).get_width(); x++) {
            shared_ptr<Block> cell = (*board).get_block(make_tuple(x, y));
            fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, 50 * x, 50 * y, 50, 50, (*cell).getColor());
        }
    }
}

void MainWindow::draw_menu() {
    fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, 50, 50, 50, 50, fl_rgb_color(255, 128, 0));
}

void MainWindow::draw() {
    Fl_Window::draw();
    
    switch (current_screen) {
    case menu_screen: draw_menu(); break;
    case board_screen: draw_board(); break;
    
    default:
        break;
    }
}

void MainWindow::set_board(shared_ptr<Board> new_board) {
    board = new_board;
}

void MainWindow::display_menu() {
    current_screen = menu_screen;
}

void MainWindow::display_board() {
    if (board) {
        current_screen = board_screen;
    }
}

void MainWindow::timer_CB(void *userdata) {
    MainWindow *o = static_cast<MainWindow*>(userdata);
    o->redraw();
    Fl::repeat_timeout(1.0/refreshPerSecond, timer_CB, userdata);
}