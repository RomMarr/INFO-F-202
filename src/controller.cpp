#include "controller.hpp"

#include "model.hpp"
#include "block.hpp"

#include <FL/Fl.H>
#include <memory>
#include <tuple>
#include <iostream>
#include <vector>

using namespace std;

Controller::Controller(shared_ptr<Board> board): board{board} {};

void Controller::select_level(int level_id) {
    board->set_level("levels/" + to_string(level_id) + ".txt");
}

void Controller::key_handler(int key_event){
    shared_ptr<Player> player = board->get_player();
    if (key_event == 32) board->reset_level(); // key_event 32 is the space bar
    if (check_lose() || check_win()) return;
    switch (key_event) {
             // REF https://www.fltk.org/doc-1.3/group__fl__events.html#ga12be48f03872da009734f557d1e761bc           
        case FL_Up:
            move_handler(make_tuple(0,-1));
            break;
        case FL_Down:
            move_handler(make_tuple(0,1));
            break;
        case FL_Right:
            move_handler(make_tuple(1,0));
            break;
        case FL_Left:
            move_handler(make_tuple(-1,0));
            break;
        default:
            break;
    }player->setWeight(0);
    check_win();
    check_lose();
}

void Controller::move_handler(tuple<int, int> move){
    shared_ptr<Player> player = board->get_player();  // get the ptr to the player
    tuple<int, int> posPlayer = player->getPos();  // position of the player
    player->setMoveAsked(move);
    if (check_move(move)){
        if (!player->isTeleported()) player->setPos(make_tuple(get<0>(posPlayer)+get<0>(player->getMoveAsked()),get<1>(posPlayer)+get<1>(player->getMoveAsked())));
        else {tuple<int, int> new_pos = make_tuple(get<0>(posPlayer) + get<0>(move),get<1>(posPlayer)+get<1>(move)); // new possible position of the player (not checked yet)
            board->teleport(new_pos);
            player->changeTeleported();
        }
        player->addStep();
    }; 
}


bool Controller::check_move(tuple<int, int> move){
    shared_ptr<Player> player = board->get_player();  // get the ptr to the player
    tuple<int, int> posPlayer = player->getPos();  // position of the player
    tuple<int, int> new_pos = make_tuple(get<0>(posPlayer) + get<0>(move),get<1>(posPlayer)+get<1>(move)); // new possible position of the player (not checked yet)
    tuple<int, int> new_pos_box = make_tuple(get<0>(new_pos) + get<0>(player->getMoveAsked()),get<1>(new_pos)+get<1>(player->getMoveAsked())); // new possible position of the box (not checked yet)

    if (!board->isInBoard(new_pos)) { // check if the player will not leave the board with its movement
        return false;
    } 
    if (player->getWeight()> 10) {  // A player can push max a weight lesser than 10
        return false;
    }
    Block::BlockType destination_type = board->get_block(new_pos)->getType();
    shared_ptr<Block> block_on_move = board->get_box_on_pos(new_pos);  // ptr to the box if there is one, nullptr if not
    if (destination_type == Block::BlockType::wall) { // if the block of arrival is a wall
        return false;
    } else if (destination_type == Block::BlockType::floor || destination_type == Block::BlockType::target){
        // if the block of arrival is a floor or a target
        if (block_on_move){  // check if ptr != nullptr
            player->setWeight(player->getWeight()+block_on_move->getWeight()); // add the weight of the box pushed by the player
            if (check_move(make_tuple(get<0>(move)+get<0>(player->getMoveAsked()), get<1>(move)+get<1>(player->getMoveAsked())))){
                // recursive call to check the next block until we have a wall, a free block or too much weight
                if (player->getWeight() > 10) return false; // too much weight for the player
                else { 
                    if (board->get_block(new_pos_box)->getType()==Block::BlockType::teleporter) {cout <<"ici"<<endl; return false;}
                    else {board->get_box_on_pos(new_pos)->setPos(new_pos_box); // modifie la position de la box
                    return true; } 
                }
            }else return false;
        }return true;
    } else if (destination_type == Block::BlockType::teleporter){ // if the block of arrival is a teleporter
        if (block_on_move) return false;
        else {player->changeTeleported();
            return true;}
    } else return false;
}

 bool Controller::isBlocked(shared_ptr<Block> box){
    tuple<int, int> pos_box = box->getPos();  // position of the box to check
    vector<tuple<int,int>> next_case;  // list of positions of cases to try to see if it's blocked
    vector<bool> blocked;  // list of booleans (true if blocked, false if not)
    next_case.push_back(make_tuple(get<0>(pos_box),get<1>(pos_box)+1));  // add position to try to the list
    next_case.push_back(make_tuple(get<0>(pos_box),get<1>(pos_box)-1));
    next_case.push_back(make_tuple(get<0>(pos_box)+1,get<1>(pos_box)));
    next_case.push_back(make_tuple(get<0>(pos_box)-1,get<1>(pos_box)));
    for (auto i: next_case){  // loop with all the elements of the liste next_case
        if (board->isInBoard(i)){  // if position (checked) is in the board
            shared_ptr<Block> box_on_case = board->get_box_on_pos(i);  // ptr to a box or nullptr if no box on the case
            if (box_on_case) { // if box on case
                if (box_on_case->getWeight()==6) blocked.push_back(true);  // heavy box blocked by another heavy box
                else blocked.push_back(false);  // if it's a light box 
            }
            else if (board->get_block(i)->getType()==Block::BlockType::wall) blocked.push_back(true); // boc blocked by a wall
            else if (board->get_block(i)->getType()==Block::BlockType::teleporter)blocked.push_back(true); // box blocked by a teleporter
            else blocked.push_back(false); // position does not block the box
        } else blocked.push_back(true);  // position is not on the board
    } return(blocked.at(0)|| blocked.at(1))&& (blocked.at(2)|| blocked.at(3));  // true if blocked at least once horizontally and once vertically
 }

 bool Controller::failure_detection(){
    bool all_blocked = true;  // true if all boxes are blocked
    bool box_blocked;  // test each box at a time
    for (shared_ptr<Block> box: board->get_boxes()) {  // go through all the boxes of the board 
        box_blocked = isBlocked(box);  // test if box is blocked
        all_blocked = (all_blocked && box_blocked);
    }if (all_blocked) return true; // all boxes are blocked
    else return false;
 }

bool Controller::check_lose(){
    shared_ptr<Player> player = board->get_player();  // get the ptr to the player
    return (player->getSteps() >= board->getMaxSteps() || failure_detection()); // true if game over

}

bool Controller::check_win(){
    shared_ptr<Player> player = board->get_player();  // get the ptr to the player
    if (board->nb_box_on_target() != board->get_boxes().size()) return false; // if not all boxes are on a target
    if (board->get_best_steps() == -1 || board->get_best_steps() > player->getSteps()) board->write_bestSteps(); // if best steps has been beaten
    return true;
}