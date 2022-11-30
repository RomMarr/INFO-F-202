#include "view.hpp"
#include "model.hpp"
#include "controller.hpp"

#include <iostream>
#include <string>
#include <memory>
#include <cassert>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>


RectangleButton::RectangleButton(int x, int y, int width, int height, std::string buttonTitle, int button_id): 
    x{x}, y{y}, width{width}, height{height}, buttonTitle{buttonTitle}, button_id{button_id} {
    
    // -1 is reserved for button not found on getButtonId function
    assert(button_id != -1);
}

void RectangleButton::draw() {
    fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, x, y, width, height, fl_rgb_color(255, 255, 255));
    fl_color(fl_rgb_color(0, 0, 0));
    fl_font(FL_HELVETICA, 12);
    fl_draw(buttonTitle.c_str(), x + 5,  (y + height / 2) + 3);
}

int RectangleButton::getButtonId(int click_x, int click_y) {
    // check horizontaly if in rectangle
    if (click_x > x && click_x < x + width) {
        if (click_y > y && click_y < y + height) {
            return button_id;
        }
    }

    return -1;
}

void LoadingScreen::draw() {
    std::string title = "SOKOBAN";
    std::string authors = "Par Romain Markowitch & Pol Marnette";

    fl_color(fl_rgb_color(0, 0, 0));
    fl_font(FL_HELVETICA, 24);
    fl_draw(title.c_str(), 50, 100);
    fl_font(FL_HELVETICA, 12);
    fl_draw(authors.c_str(), 50,  120);
}

MainMenu::MainMenu(shared_ptr<Controller> controller): controller{controller} {};

void MainMenu::draw() {
    if (buttons.size() == 0) {
        buttons.push_back(make_shared<RectangleButton>(50, 50, 30, 30, "0"));
        buttons.push_back(make_shared<RectangleButton>(100, 50, 30, 30, "1", 1));
    }

    for (shared_ptr<RectangleButton> btn: buttons) {
        btn->draw();
    }
}

void MainMenu::onWindowClicked(int x, int y) {
    for (shared_ptr<RectangleButton> btn: buttons) {
        int btn_id = btn->getButtonId(x, y);
        if (btn_id != -1) {
            controller->select_level(btn_id);
        }
    }
}

MainWindow::MainWindow(MainMenu menu): Fl_Window(500, 500, 500, 500, "Sokoban"), menu(menu) {
    Fl::add_timeout(1.0/refreshPerSecond, timer_CB, this);
    Fl::add_timeout(1.0, loading_screen_timeout, this);
    // resizable(this);
}

void MainWindow::set_controller(shared_ptr<Controller> new_controller) {
    controller = new_controller;
}

void MainWindow::draw_board() {
    for (size_t y = 0; y < board->get_height(); y++) {
        for (size_t x = 0; x < board->get_width(); x++) {
            shared_ptr<Player> player_here = board->get_player_on_pos(make_tuple(x, y));
            shared_ptr<Block> box_here = board->get_box_on_pos(make_tuple(x, y));

            if (player_here) {
                fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, 50 * x, 50 * y, 50, 50, fl_rgb_color(0, 0, 255));
            } else if (box_here) {
                fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, 50 * x, 50 * y, 50, 50, box_here->getColor());
            } else {
                shared_ptr<Block> cell = board->get_block(make_tuple(x, y));
                fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, 50 * x, 50 * y, 50, 50, cell->getColor());
            }
        }
    }
}

void MainWindow::draw() {
    Fl_Window::draw();

    if (board->should_show_board()) {
        draw_board();
    } else {
        switch (current_screen) {
            case loading_screen: LoadingScreen::draw(); break;
            case menu_screen: menu.draw(); break;
         
            default: break;
        }
    }    
    
}

int MainWindow::handle(int event) {
    if (event == FL_PUSH && current_screen == menu_screen) menu.onWindowClicked(Fl::event_x(), Fl::event_y());
    if (event == FL_KEYDOWN && board->should_show_board()) controller->key_handler(Fl::event_key());
}

void MainWindow::set_board(shared_ptr<Board> new_board) {
    board = new_board;
}

void MainWindow::display_menu() {
    current_screen = menu_screen;
}

void MainWindow::timer_CB(void *userdata) {
    MainWindow *o = static_cast<MainWindow*>(userdata);
    o->redraw();
    Fl::repeat_timeout(1.0/refreshPerSecond, timer_CB, userdata);
}

void MainWindow::loading_screen_timeout(void *userdata) {
    MainWindow *o = static_cast<MainWindow*>(userdata);
    o->display_menu();
}