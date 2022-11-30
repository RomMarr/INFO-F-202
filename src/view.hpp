#ifndef _VIEW_H
#define _VIEW_H

#include "controller.hpp"
#include "model.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <memory>
#include <string>
#include <vector>

class RectangleButton {
    int x, y, width, height, button_id;
    std::string buttonTitle;
    bool is_active = false;
public:
    RectangleButton(int x, int y, int width, int height, std::string buttonTitle, int button_id = 0);
    void draw();
    bool contains(int x, int y);
    int get_button_id();
    void set_is_active(bool value);
    bool get_is_active();
};

class LoadingScreen {
public:
    static void draw();
};

class MainMenu {
    shared_ptr<Controller> controller;
    vector<shared_ptr<RectangleButton>> level_selection_btn;
    shared_ptr<RectangleButton> play_btn;
public:
    MainMenu(shared_ptr<Controller> controller);
    static void select_level(shared_ptr<Controller> controller, int id);
    void draw();
    void onWindowClicked(int x, int y);
};

class MainWindow: public Fl_Window {
    MainMenu menu;
    shared_ptr<Board> board;
    shared_ptr<Controller> controller;
    shared_ptr<RectangleButton> reset_btn;
    shared_ptr<RectangleButton> back_to_menu_btn;
    static constexpr inline double refreshPerSecond = 60;
    bool show_loading = true;
    void draw_board();
    void draw_board_informations();
    void draw_menu();
public:
    MainWindow(MainMenu);
    void set_controller(shared_ptr<Controller> controller);
    void set_board(shared_ptr<Board> new_board);
    void draw() override;
    int handle(int event) override;
    void hide_loading();
    static void timer_CB(void *userdata);
    static void loading_screen_timeout(void *userdata);
};

#endif