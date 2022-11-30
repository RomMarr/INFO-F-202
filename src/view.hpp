#ifndef _VIEW_H
#define _VIEW_H

#include "model.hpp"
#include "controller.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <memory>


class LoadingScreen {
public:
    static void draw();
};

class MainMenu {
public:
    void draw();
};

class MainWindow: public Fl_Window {
    MainMenu menu;
    shared_ptr<Board> board;
    shared_ptr<Controller> controller;
    static constexpr inline double refreshPerSecond = 60;
    enum ScreenType { loading_screen, menu_screen, board_screen };
    ScreenType current_screen = loading_screen;
    void draw_board();
    void draw_menu();
public:
    MainWindow(MainMenu);
    void set_controller(shared_ptr<Controller> controller);
    void set_board(shared_ptr<Board> new_board);
    void draw() override;
    int handle(int event) override;
    void display_menu();
    void display_board();
    static void timer_CB(void *userdata);
    static void loading_screen_timeout(void *userdata);
};

#endif