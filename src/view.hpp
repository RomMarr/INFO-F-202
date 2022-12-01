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
    std::string button_title;
    bool is_active = false;
public:
    RectangleButton(int x, int y, int width, int height, std::string button_title, int button_id = 0);
    void draw();
    bool contains(int x, int y);
    int getButtonId();
    void setIsActive(bool value);
    bool getIsActive();
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
    static void selectLevel(shared_ptr<Controller> controller, int id);
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
    void drawBoard();
    void drawBoardInformations();
    void drawMenu();
public:
    MainWindow(MainMenu);
    void setController(shared_ptr<Controller> controller);
    void setBoard(shared_ptr<Board> new_board);
    void draw() override;
    int handle(int event) override;
    void hideLoading();
    static void timerCB(void *userdata);
    static void loadingScreenTimeout(void *userdata);
};

#endif