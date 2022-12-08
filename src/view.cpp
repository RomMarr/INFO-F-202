#include "view.hpp"
#include "model.hpp"
#include "controller.hpp"
#include "constants.hpp"

#include <iostream>
#include <string>
#include <cmath>
#include <memory>
#include <cassert>
#include <algorithm>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>


RectangleButton::RectangleButton(int x, int y, int width, int height, std::string button_title, int button_id): 
    x{x}, y{y}, width{width}, height{height}, button_id{button_id}, button_title{button_title} {
    
    // -1 is reserved for button not found on getButtonId function
    assert(button_id != -1);
}

void RectangleButton::draw() {
    fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, x, y, width, height, (is_active ? fl_rgb_color(153, 204, 255) : fl_rgb_color(255, 255, 255)));
    fl_color(fl_rgb_color(0, 0, 0));
    fl_font(FL_HELVETICA, 12);
    fl_draw(button_title.c_str(), x + 5,  (y + height / 2) + 3);
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

int RectangleButton::getButtonId() {
    return button_id;
}

void RectangleButton::setIsActive(bool value) {
    is_active = value;
}

bool RectangleButton::getIsActive() {
    return is_active;
}

void LoadingScreen::draw() {
    fl_color(fl_rgb_color(0, 0, 0));
    fl_font(FL_HELVETICA, 24);
    fl_draw(LOADING_TITLE.c_str(), 50, 100);
    fl_font(FL_HELVETICA, 12);
    fl_draw(LOADING_AUTHORS.c_str(), 50,  120);
}

MainMenu::MainMenu(shared_ptr<Controller> controller): controller{controller} {};

void MainMenu::draw() {
    if (level_selection_btn.size() == 0) {
        for (int i =0; i<NUMBER_OF_LEVELS; i++){
            int posY = round(i/3); // level's buttoms are drawn 3 by 3
            level_selection_btn.push_back(make_shared<RectangleButton>(50 + 40*(i%3),50 + 40*posY, 30, 30, to_string(i),i));
        }
    }

    if (!play_btn) {
        double fraction = NUMBER_OF_LEVELS/(3);
        int posY = round(fraction);
        play_btn = make_shared<RectangleButton>(50, 90+ 40*posY, 110, 30, PLAY_BUTTON_TITLE);
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
            if (btn->getIsActive()) {
                controller->selectLevel(btn->getButtonId());
                break;
            }
        }
    }

    for (shared_ptr<RectangleButton> btn: level_selection_btn) {
        if (btn->contains(x, y)) {
            btn->setIsActive(true);
        } else {
            btn->setIsActive(false);
        }
    }
}

MainWindow::MainWindow(MainMenu menu): Fl_Window(500, 500, 750, 500, WINDOW_TITLE.c_str()), menu(menu) {
    Fl::add_timeout(1.0 / REFRESH_RATE, timerCB, this);
    Fl::add_timeout(LOADING_SCREEN_TIMEOUT, loadingScreenTimeout, this);
}

void MainWindow::setController(shared_ptr<Controller> new_controller) {
    controller = new_controller;
}

void MainWindow::drawBoard() {
    int block_size = std::min(500 / board->getWidth(), 500 / board->getHeight());

    int y_offset = (500 - (block_size * board->getHeight())) / 2;

    for (int y = 0; y < board->getHeight(); y++) {
        for (int x = 0; x < board->getWidth(); x++) {
            shared_ptr<Player> player_here = board->getPlayer(Point{x, y});
            shared_ptr<Block> box_here = board->getBox(Point{x, y});

            int pos_x = block_size * x;
            int pos_y = y_offset + block_size * y;

            if (player_here) {
                fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, pos_x, pos_y, block_size, block_size, PLAYER_COLOR);
            } else if (box_here) {
                fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, pos_x, pos_y, block_size, block_size, fl_rgb_color(0, 0, 0));
                fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, pos_x + 1, pos_y + 1, block_size - 2, block_size - 2, box_here->getColor());
            } else {
                shared_ptr<Block> cell = board->getBlock(Point{x, y});
                if (cell->getType() == Block::BlockType::target) {
                    fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, pos_x  + (block_size / 4), pos_y  + (block_size / 4), block_size / 2, block_size / 2, cell->getColor());
                } else {
                    fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, pos_x, pos_y, block_size, block_size, cell->getColor());
                }
            }
        }
    }

    fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, block_size * board->getWidth(), 0, 1, 500, fl_rgb_color(0, 0, 0));

    drawBoardInformations();
}

void MainWindow::drawBoardInformations() {
    int pos_x = 525;

    std::string title = "Level " + to_string(board->getLvl());
    std::string steps_information = "Steps " + to_string(board->getPlayer()->getSteps()) + "/" + to_string(board->getMaxSteps());
    std::string best_steps = board->getBestSteps() == -1 ? "No best score" : "Best : " + to_string(board->getBestSteps());
    std::string box_on_pos = "Box : " + to_string(board->nbBoxOnTarget()) + "/" + to_string(board->getBoxes().size());

    fl_font(FL_HELVETICA_BOLD, 32);
    if (controller->checkWin()) {
        fl_color(fl_rgb_color(0, 102, 0));
        fl_draw(WIN_TITLE.c_str(), pos_x, 50);
    } else if (controller->checkLose()) {
        fl_color(fl_rgb_color(204, 0, 0));
        fl_draw(LOST_TITLE.c_str(), pos_x, 50);
    }

    fl_color(fl_rgb_color(0, 0, 0));
    fl_font(FL_HELVETICA, 24);
    fl_draw(title.c_str(), pos_x, 120);

    fl_color((board->getPlayer()->getSteps() >= board->getMaxSteps() ?  fl_rgb_color(255, 0, 0) : fl_rgb_color(0, 0, 0)));
    fl_font(FL_HELVETICA, 14);
    fl_draw(steps_information.c_str(), pos_x, 150);

    fl_color(fl_rgb_color(0, 0, 0));
    fl_draw(best_steps.c_str(), pos_x, 170);

    fl_draw(box_on_pos.c_str(), pos_x, 190);

    if (!reset_btn) reset_btn = make_shared<RectangleButton>(pos_x, 220, 200, 30, RESET_BUTTON_TITLE);
    if (!back_to_menu_btn) back_to_menu_btn = make_shared<RectangleButton>(pos_x, 270, 200, 30, CHANGE_LEVEL_BUTTON_TITLE);

    reset_btn->draw();
    back_to_menu_btn->draw();
}

void MainWindow::draw() {
    Fl_Window::draw();

    if (show_loading) {
        LoadingScreen::draw();
    } else if (board->shouldShowBoard()) {
        drawBoard();
    } else {
        menu.draw();
    }
}

int MainWindow::handle(int event) {
    if (event == FL_PUSH) {
        if (board->shouldShowBoard()) {
            if (reset_btn && reset_btn->contains(Fl::event_x(), Fl::event_y())) board->resetLevel();
            if (back_to_menu_btn && back_to_menu_btn->contains(Fl::event_x(), Fl::event_y())) board->setShowBoard(false);
            return 1;    
        } else if (!show_loading) {
            menu.onWindowClicked(Fl::event_x(), Fl::event_y());
            return 1;    
        } 
    }
    if (event == FL_KEYDOWN && board->shouldShowBoard()) {
        controller->keyHandler(Fl::event_key());
        return 1;    
    }

    return 0;
}

void MainWindow::setBoard(shared_ptr<Board> new_board) {
    board = new_board;
}

void MainWindow::hideLoading() {
    show_loading = false;
}

void MainWindow::timerCB(void *userdata) {
    MainWindow *window = static_cast<MainWindow*>(userdata);
    window->redraw();
    Fl::repeat_timeout(1.0 / REFRESH_RATE, timerCB, userdata);
}

void MainWindow::loadingScreenTimeout(void *userdata) {
    MainWindow *window = static_cast<MainWindow*>(userdata);
    window->hideLoading();
}