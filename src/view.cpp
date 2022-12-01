#include "view.hpp"
#include "model.hpp"
#include "controller.hpp"

#include <iostream>
#include <string>
#include <memory>
#include <cassert>
#include <algorithm>
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
    fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, x, y, width, height, (is_active ? fl_rgb_color(153, 204, 255) : fl_rgb_color(255, 255, 255)));
    fl_color(fl_rgb_color(0, 0, 0));
    fl_font(FL_HELVETICA, 12);
    fl_draw(buttonTitle.c_str(), x + 5,  (y + height / 2) + 3);
}

bool RectangleButton::contains(int click_x, int click_y) {
    // check horizontaly if in rectangle
    if (click_x > x && click_x < x + width) {
        if (click_y > y && click_y < y + height) {
            return true;
        }
    }

    return false;
}

int RectangleButton::get_button_id() {
    return button_id;
}

void RectangleButton::set_is_active(bool value) {
    is_active = value;
}

bool RectangleButton::get_is_active() {
    return is_active;
}

void LoadingScreen::draw() {
    std::string title = "SOKOBAN";
    std::string authors = "By Romain Markowitch & Pol Marnette";

    fl_color(fl_rgb_color(0, 0, 0));
    fl_font(FL_HELVETICA, 24);
    fl_draw(title.c_str(), 50, 100);
    fl_font(FL_HELVETICA, 12);
    fl_draw(authors.c_str(), 50,  120);
}

MainMenu::MainMenu(shared_ptr<Controller> controller): controller{controller} {};

void MainMenu::draw() {
    if (level_selection_btn.size() == 0) {
        level_selection_btn.push_back(make_shared<RectangleButton>(50, 50, 30, 30, "0"));
        level_selection_btn.push_back(make_shared<RectangleButton>(100, 50, 30, 30, "1", 1));
        level_selection_btn.push_back(make_shared<RectangleButton>(150, 50, 30, 30, "2", 2));
        level_selection_btn.push_back(make_shared<RectangleButton>(200, 50, 30, 30, "3", 3));
    }

    if (!play_btn) {
        play_btn = make_shared<RectangleButton>(50, 100, 130, 30, "Play");
    }

    for (shared_ptr<RectangleButton> btn: level_selection_btn) {
        btn->draw();
    }
    play_btn->draw();
}

void MainMenu::onWindowClicked(int x, int y) {
    // If click on play
    if (play_btn->contains(x, y)) {
        // Get btn active and play level associate
        for (shared_ptr<RectangleButton> btn: level_selection_btn) {
            if (btn->get_is_active()) {
                controller->select_level(btn->get_button_id());
                break;
            }
        }
    }

    for (shared_ptr<RectangleButton> btn: level_selection_btn) {
        if (btn->contains(x, y)) {
            btn->set_is_active(true);
        } else {
            btn->set_is_active(false);
        }
    }
}

MainWindow::MainWindow(MainMenu menu): Fl_Window(500, 500, 750, 500, "Sokoban"), menu(menu) {
    Fl::add_timeout(1.0/refreshPerSecond, timer_CB, this);
    Fl::add_timeout(1.0, loading_screen_timeout, this);
}

void MainWindow::set_controller(shared_ptr<Controller> new_controller) {
    controller = new_controller;
}

void MainWindow::draw_board() {
    int block_size = std::min(500 / board->get_width(), 500 / board->get_height());

    int y_offset = (500 - (block_size * board->get_height())) / 2;

    for (size_t y = 0; y < board->get_height(); y++) {
        for (size_t x = 0; x < board->get_width(); x++) {
            shared_ptr<Player> player_here = board->get_player_on_pos(make_tuple(x, y));
            shared_ptr<Block> box_here = board->get_box_on_pos(make_tuple(x, y));

            int pos_x = block_size * x;
            int pos_y = y_offset + block_size * y;

            if (player_here) {
                fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, pos_x, pos_y, block_size, block_size, fl_rgb_color(0, 0, 255));
            } else if (box_here) {
                fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, pos_x, pos_y, block_size, block_size, box_here->getColor());
            } else {
                shared_ptr<Block> cell = board->get_block(make_tuple(x, y));
                if (cell->getType() == Block::BlockType::target) {
                    fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, pos_x  + (block_size / 4), pos_y  + (block_size / 4), block_size / 2, block_size / 2, cell->getColor());
                } else {
                    fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, pos_x, pos_y, block_size, block_size, cell->getColor());
                }
            }
        }
    }

    fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, block_size * board->get_width(), 0, 1, 500, fl_rgb_color(0, 0, 0));

    draw_board_informations();
}

void MainWindow::draw_board_informations() {
    int pos_x = 525;

    std::string won_title = "Gagné";
    std::string lose_title = "Perdu";

    std::string title = "Level " + to_string(board->getLvl());
    std::string steps_information = "Steps " + to_string(board->get_player()->getSteps()) + "/" + to_string(board->getMaxSteps());
    std::string best_steps = board->get_best_steps() == -1 ? "No best score" : "Best : " + to_string(board->get_best_steps());
    std::string box_on_pos = "Box : " + to_string(board->nb_box_on_target()) + "/" + to_string(board->get_boxes().size());

    fl_font(FL_HELVETICA_BOLD, 32);
    if (controller->check_win()) {
        fl_color(fl_rgb_color(0, 102, 0));
        fl_draw(won_title.c_str(), pos_x, 50);
    } else if (controller->check_lose()) {
        fl_color(fl_rgb_color(204, 0, 0));
        fl_draw(lose_title.c_str(), pos_x, 50);
    }

    fl_color(fl_rgb_color(0, 0, 0));
    fl_font(FL_HELVETICA, 24);
    fl_draw(title.c_str(), pos_x, 120);

    fl_color((board->get_player()->getSteps() >= board->getMaxSteps() ?  fl_rgb_color(255, 0, 0) : fl_rgb_color(0, 0, 0)));
    fl_font(FL_HELVETICA, 14);
    fl_draw(steps_information.c_str(), pos_x, 150);

    fl_color(fl_rgb_color(0, 0, 0));
    fl_draw(best_steps.c_str(), pos_x, 170);

    fl_draw(box_on_pos.c_str(), pos_x, 190);

    if (!reset_btn) reset_btn = make_shared<RectangleButton>(pos_x, 220, 200, 30, "Reset level");
    if (!back_to_menu_btn) back_to_menu_btn = make_shared<RectangleButton>(pos_x, 270, 200, 30, "Change level");

    reset_btn->draw();
    back_to_menu_btn->draw();
}

void MainWindow::draw() {
    Fl_Window::draw();

    if (show_loading) {
        LoadingScreen::draw();
    } else if (board->should_show_board()) {
        draw_board();
    } else {
        menu.draw();
    }
}

int MainWindow::handle(int event) {
    if (event == FL_PUSH) {
        if (board->should_show_board()) {
            if (reset_btn && reset_btn->contains(Fl::event_x(), Fl::event_y())) board->reset_level();
            if (back_to_menu_btn && back_to_menu_btn->contains(Fl::event_x(), Fl::event_y())) board->set_show_board(false);
        } else if (!show_loading) {
            menu.onWindowClicked(Fl::event_x(), Fl::event_y());
        } 
    }
    if (event == FL_KEYDOWN && board->should_show_board()) controller->key_handler(Fl::event_key());
}

void MainWindow::set_board(shared_ptr<Board> new_board) {
    board = new_board;
}

void MainWindow::hide_loading() {
    show_loading = false;
}

void MainWindow::timer_CB(void *userdata) {
    MainWindow *o = static_cast<MainWindow*>(userdata);
    o->redraw();
    Fl::repeat_timeout(1.0/refreshPerSecond, timer_CB, userdata);
}

void MainWindow::loading_screen_timeout(void *userdata) {
    MainWindow *o = static_cast<MainWindow*>(userdata);
    o->hide_loading();
}