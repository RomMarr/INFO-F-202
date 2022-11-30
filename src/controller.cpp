#include "controller.hpp"
#include "model.hpp"

#include <FL/Fl.H>
#include <memory>
#include <tuple>
#include <iostream>

using namespace std;

Controller::Controller(shared_ptr<Board> board): board{board} {};


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
    if (check_lose()) cout << "LOOOOOOSE"<<endl;;
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

//  bool Controller::isBlocked(shared_ptr<Block> box){
//     tuple<int, int> pos_box = box->getPos();
//     vector<tuple<int,int>> next;
//     vector<bool> blocked;
//     next.push_back(make_tuple(get<0>(pos_box),get<1>(pos_box)+1));
//     next.push_back(make_tuple(get<0>(pos_box),get<1>(pos_box)-1));
//     next.push_back(make_tuple(get<0>(pos_box)+1,get<1>(pos_box)));
//     next.push_back(make_tuple(get<0>(pos_box)-1,get<1>(pos_box)));
//     for (auto i: next){
//         bool a;
//         if (board->isInBoard(i)){
//             shared_ptr<Block> test = board->get_box_on_pos(i);
//             if (test) if (test->getWeight()==6) a= true;
//             else if (board->get_block(i)->getType()==Block::BlockType::wall) a= true;
//             else if (board->get_block(i)->getType()==Block::BlockType::teleporter) a=true;
//             else a = false;
//         } else a= true;
//     blocked.push_back(a);
//     }
//     return ((blocked.pop_back()||blocked.pop_back()) && (blocked.pop_back()||blocked.pop_back()));
//  }

 bool Controller::failure_detection(){
    for (shared_ptr<Block> box: board->get_boxes()) {
        //if (!isBlocked(box)) return false;
    }return true;
 }

bool Controller::check_lose(){
    shared_ptr<Player> player = board->get_player();  // get the ptr to the player
    return (player->getSteps() >= board->getMaxSteps()); // || failure_detection());

}

bool Controller::check_win(){
    shared_ptr<Player> player = board->get_player();  // get the ptr to the player
    for (shared_ptr<Block> box: board->get_boxes()) {
        if (board->get_block(box->getPos())->getType() != Block::BlockType::target){
            return false;
        }
     } cout << "WINNNNNNNN" <<endl;
     if (board->read_bestSteps()> player->getSteps()) board->write_bestSteps();
     return true;
}