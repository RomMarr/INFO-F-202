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


RectangleButton::RectangleButton(Point set_position, int width, int height, std::string button_title, int button_id): 
    position{set_position}, width{width}, height{height}, button_id{button_id}, button_title{button_title} {
    
    // -1 is reserved for button not found on getButtonId function
    assert(button_id != -1);
}

void RectangleButton::draw() {
    fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, position.getPosX(), position.getPosY(), width, height, (is_active ? fl_rgb_color(153, 204, 255) : fl_rgb_color(255, 255, 255)));
    fl_color(fl_rgb_color(0, 0, 0));
    fl_font(FL_HELVETICA, 12);
    fl_draw(button_title.c_str(), position.getPosX() + 5,  (position.getPosY() + height / 2) + 3);
}

bool RectangleButton::contains(Point clicked_position) {
    // check horizontaly if contained
    if (clicked_position.getPosX() > position.getPosX() && clicked_position.getPosX() < position.getPosX() + width) {
        // check vertically if contained
        if (clicked_position.getPosY() > position.getPosY() && clicked_position.getPosY() < position.getPosY() + height) {
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
    // If there is no level selection button already initialised, initialise them
    if (level_selection_btn.size() == 0) {
        for (int index_level = 0; index_level<NUMBER_OF_LEVELS; index_level++){
            int posY = round(index_level/3); // level's buttons in a 3 by 3 grid
            Point position{50 + 40 * (index_level%3), 50 + 40 * posY};
            level_selection_btn.push_back(make_shared<RectangleButton>(position, 30, 30, to_string(index_level),index_level));
        }
    }

    // If there is no play button already initialised, initialise it
    if (!play_btn) {
        int posY = round(NUMBER_OF_LEVELS/3);
        play_btn = make_shared<RectangleButton>(Point{50, 90 + 40 * posY}, 110, 30, PLAY_BUTTON_TITLE);
    }

    // Draw all the buttons
    for (auto btn: level_selection_btn) {
        btn->draw();
    }
    play_btn->draw();
}

void MainMenu::onWindowClicked(Point clicked_position) {
    // If click on play
    if (play_btn->contains(clicked_position)) {
        // Get btn active and play level associate
        for (shared_ptr<RectangleButton> btn: level_selection_btn) {
            if (btn->getIsActive()) {
                controller->selectLevel(btn->getButtonId());
                break;
            }
        }
    }

    // Check if clicked on a level selection button
    for (auto btn: level_selection_btn) {
        if (btn->contains(clicked_position)) {
            btn->setIsActive(true);
        } else {
            btn->setIsActive(false);
        }
    }
}

MainWindow::MainWindow(MainMenu menu): Fl_Window(500, 500, 750, 500, WINDOW_TITLE.c_str()), menu(menu) {
    Fl::add_timeout(1.0 / REFRESH_RATE, timerCB, this); // Called on every refresh to redraw
    Fl::add_timeout(LOADING_SCREEN_TIMEOUT, loadingScreenTimeout, this); // Called after one second to hide the loading screen
}

void MainWindow::setController(shared_ptr<Controller> new_controller) {
    controller = new_controller;
}

void MainWindow::drawBoard() {
    shared_ptr<Player> player = board->getPlayer();

    // Block size to have the board within the 500 by 500 space reserved for the board
    int block_size = std::min(500 / board->getWidth(), 500 / board->getHeight());
    
    // The offset to have the board horizontally centered
    int y_offset = (500 - (block_size * board->getHeight())) / 2;

    // Draw the blocks of the board
    for (int y = 0; y < board->getHeight(); y++) {
        for (int x = 0; x < board->getWidth(); x++) {
            int pos_x = block_size * x;
            int pos_y = y_offset + block_size * y;

            shared_ptr<Block> cell = board->getBlock(Point{x, y});
            if (cell->getType() == Block::BlockType::target) {
                fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, pos_x  + (block_size / 4), pos_y  + (block_size / 4), block_size / 2, block_size / 2, cell->getColor());
            } else {
                fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, pos_x, pos_y, block_size, block_size, cell->getColor());
            }
        }
    }

    // Draw the boxes
    for (auto box: board->getBoxes()) {
        Point position = box->getAnimation().getAnimatedPosition(box->getPos()) * block_size;
        fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, position.getPosX(), y_offset + position.getPosY(), block_size, block_size, fl_rgb_color(0, 0, 0));
        fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, position.getPosX() + 1, y_offset + position.getPosY() + 1, block_size - 2, block_size - 2, box->getColor());
    }

    // Draw the player
    Point player_position = player->getAnimation().getAnimatedPosition(player->getPos()) * block_size;
    fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, player_position.getPosX(), y_offset + player_position.getPosY(), block_size, block_size, PLAYER_COLOR);

    // Separator between board and menu
    fl_draw_box(Fl_Boxtype::FL_FLAT_BOX, block_size * board->getWidth(), 0, 1, 500, fl_rgb_color(0, 0, 0));

    drawBoardInformations();
}

void MainWindow::drawBoardInformations() {
    int pos_x = 525;

    std::string title = "Level " + to_string(board->getLvl());
    std::string steps_information = "Steps " + to_string(board->getPlayer()->getSteps()) + "/" + to_string(board->getMaxSteps());
    std::string best_steps = board->getBestSteps() == -1 ? "No best score" : "Best : " + to_string(board->getBestSteps());
    std::string box_on_pos = "Box : " + to_string(board->nbBoxOnTarget()) + "/" + to_string(board->getBoxes().size());

    // Win/lose indicator
    fl_font(FL_HELVETICA_BOLD, 32);
    if (board->checkWin()) {
        fl_color(fl_rgb_color(0, 102, 0));
        fl_draw(WIN_TITLE.c_str(), pos_x, 50);
    } else if (board->checkLose()) {
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

    if (!reset_btn) reset_btn = make_shared<RectangleButton>(Point{pos_x, 220}, 200, 30, RESET_BUTTON_TITLE);
    if (!back_to_menu_btn) back_to_menu_btn = make_shared<RectangleButton>(Point{pos_x, 270}, 200, 30, CHANGE_LEVEL_BUTTON_TITLE);

    reset_btn->draw();
    back_to_menu_btn->draw();
}

void MainWindow::draw() {
    Fl_Window::draw();

    if (show_loading) {
        LoadingScreen::draw();
    } else if (board->shouldShowBoard()) {
        controller->animationHandler();
        drawBoard();
    } else {
        menu.draw();
    }
}

int MainWindow::handle(int event) {
    if (event == FL_PUSH) {
        if (board->shouldShowBoard()) {
            if (reset_btn && reset_btn->contains({Fl::event_x(), Fl::event_y()})) board->resetLevel();
            if (back_to_menu_btn && back_to_menu_btn->contains({Fl::event_x(), Fl::event_y()})) board->setShowBoard(false);
            return 1;    
        } else if (!show_loading) {
            menu.onWindowClicked({Fl::event_x(), Fl::event_y()});
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