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
    board->setLevel("levels/" + to_string(level_id) + ".txt"); // set the level to correspond the file chosen
}

void Controller::keyHandler(int key_event){ // handle the keys pushed from the keyboard
    shared_ptr<Player> player = board->getPlayer();  //ptr to the player
    if (key_event == 32) board->resetLevel(); // key_event 32 is the space bar
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
    shared_ptr<Player> player = board->getPlayer();  // get the ptr to the player
    Point pos_player = player->getPos();  // position of the player
    player->setMoveAsked(move); // change the move asked by the player
    if (board->checkMove(move)){  // if the move is authorized
        if (!player->isTeleported()) { // if the player do a normal move
            Point move_asked = player->getMoveAsked();
            Point new_pos = pos_player + move_asked;
            player->setPos(new_pos); // change de position of the player
        } else {
            Point new_pos = pos_player + move;
            board->teleport(new_pos); // check if the play can teleport and does it if he can
            player->changeTeleported();
        }
        player->addStep();
    }; 
}

void Controller::moveBox(shared_ptr<Block> box, Point new_pos){
    box->setPos(new_pos);
}

void Controller::movePlayer(Point new_pos){
    shared_ptr<Player> player = board->getPlayer();  // get the ptr to the player
    player->setPos(new_pos);
}