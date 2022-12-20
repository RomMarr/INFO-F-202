#include "controller.hpp"

#include "model.hpp"
#include "block.hpp"
#include "player.hpp"
#include "constants.hpp"
#include "point.hpp"

#include <FL/Fl.H>
#include <memory>
#include <tuple>
#include <iostream>
#include <vector>

using namespace std;


Controller::Controller(shared_ptr<Board> board): board{board} {};

void Controller::selectLevel(int level_id) {
    board->setLevel("levels/" + to_string(level_id) + ".txt"); 
    // set the level to correspond the file chosen
}

void Controller::keyHandler(int key_event){ // handle the keys pushed from the keyboard
    shared_ptr<Player> player = board->getPlayer();
    if (player->getAnimation().isAnimated()) return; // If being animated, does nothing

    if (key_event == 32) board->resetLevel(); // key_event 32 is the space bar
    if (board->checkWin() || board->checkLose()) return;
    switch (key_event) {
    // REF https://www.fltk.org/doc-1.3/group__fl__events.html#ga12be48f03872da009734f557d1e761bc           
        case FL_Up:
            moveHandler(POSSIBLE_MOVE_UP);
            break;
        case FL_Down:
            moveHandler(POSSIBLE_MOVE_DOWN);
            break;
        case FL_Right:
            moveHandler(POSSIBLE_MOVE_RIGHT);
            break;
        case FL_Left:
            moveHandler(POSSIBLE_MOVE_LEFT);
            break;
        default:
            break;
    }player->setWeight(0);  // player doesn't push boxes anymore
    board->checkWin();
    board->checkLose();
}

void Controller::moveHandler(const Point &move){
    shared_ptr<Player> player = board->getPlayer();
    Point pos_player = player->getPos();
    player->setMoveAsked(move);
    if (board->checkMove(move)){  // if the move is authorized
        if (!player->isTeleported()) { // if the player do a normal move
            Point move_asked = player->getMoveAsked();
            Point new_pos = pos_player + move_asked;  // player's destination
            player->getAnimation().animate(player->getPos(), move_asked); // start the animation
            player->setPos(new_pos);
        } else { // if the player go to a teleporter
            Point new_pos = pos_player + move;
            board->teleport(new_pos); // teleport the player to the other teleporter
            player->changeTeleported();
        } player->addStep();
    }; 
}

void Controller::animationHandler() {
    auto player = board->getPlayer();
    player->getAnimation().computeAnimation(); // move the player little by little

    for (auto box: board->getBoxes()) {
        box->getAnimation().computeAnimation();  // move the boxes little by little
    }
}
