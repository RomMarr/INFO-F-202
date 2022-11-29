#include "controller.hpp"
#include "model.hpp"

#include <FL/Fl.H>
#include <memory>
#include <tuple>
#include <iostream>

using namespace std;

Controller::Controller(shared_ptr<Board> board): board{board} {};

void Controller::move_request(){

};


void Controller::key_handler(int key_event){
    shared_ptr<Player> player = board->get_player();
    tuple<int, int>actual_pos = player->getPos();
    
    switch (key_event) {
             // REF https://www.fltk.org/doc-1.3/group__fl__events.html#ga12be48f03872da009734f557d1e761bc           
        case FL_Up:
            player->setMoveAsked(make_tuple(0,-1));
            if (check_move(make_tuple(0,-1))){
                player->setPos(make_tuple(get<0>(actual_pos),get<1>(actual_pos) - 1));
                player->addStep();
                break;
            }; break;
        case FL_Down:
            player->setMoveAsked(make_tuple(0,1));
            if (check_move(make_tuple(0,1))){
                player->setPos(make_tuple(get<0>(actual_pos),get<1>(actual_pos) + 1));
                player->addStep();
                break;
            }; break;
        case FL_Right:
            player->setMoveAsked(make_tuple(1,0));
            if (check_move(make_tuple(1,0))){
                player->setPos(make_tuple(get<0>(actual_pos) + 1,get<1>(actual_pos)));
                player->addStep();
                break;
            }; break;
        case FL_Left:
            player->setMoveAsked(make_tuple(-1,0));
            if (check_move(make_tuple(-1,0))){
                player->setPos(make_tuple(get<0>(actual_pos) - 1,get<1>(actual_pos)));
                player->addStep();
                break;
            }; break;
        default:
            break;
    }player->setWeight(0);
}


bool Controller::check_move(tuple<int, int> move){
    shared_ptr<Player> player = board->get_player();  // get the ptr to the player

    tuple<int, int> posPlayer = player->getPos();  // position of the player
    tuple<int, int> new_pos = make_tuple(get<0>(posPlayer) + get<0>(move),get<1>(posPlayer)+get<1>(move)); // new possible position of the player (not checked yet)
    tuple<int, int> new_pos_box = make_tuple(get<0>(new_pos) + get<0>(player->getMoveAsked()),get<1>(new_pos)+get<1>(player->getMoveAsked())); // new possible position of the box (not checked yet)

    Block::BlockType destination_type = board->get_block(new_pos)->getType();

    if ((get<0>(new_pos)<0 || get<0>(new_pos)>= board->get_width()) || (get<1>(new_pos)<0 || get<1>(new_pos)>= board->get_height())) {
        // check if the player will not leave the board with its movement
        return false;
    }
    if (player->getWeight()> 10) {  // A player can push max a weight lesser than 10
        return false;
    }
    if (destination_type == Block::BlockType::wall) { // if the block of arrival is a wall
        return false;
    } else if (destination_type == Block::BlockType::floor || destination_type == Block::BlockType::target){
        // if the block of arrival is a floor or a target
        shared_ptr<Block> block_on_move = board->get_box_on_pos(new_pos);  // ptr to the box if there is one, nullptr if not
       if (block_on_move){  // check if ptr != nullptr
            player->setWeight(player->getWeight()+block_on_move->getWeight()); // add the weight of the box pushed by the player
            if (check_move(make_tuple(get<0>(move)+get<0>(player->getMoveAsked()), get<1>(move)+get<1>(player->getMoveAsked())))){
                // recursive call to check the next block until we have a wall, a free block or too much weight
                if (player->getWeight() > 10) return false; // too much weight for the player
                else {board->get_box_on_pos(new_pos)->setPos(new_pos_box); // modifie la position de la box
                    return true; 
                }
            }else return false;
        }return true;

    } else if (destination_type == Block::BlockType::teleporter){ // if the block of arrival is a teleporter

    } else return false;
}

bool Controller::check_end(){
    //shared_ptr<Player> player = board->get_player();  // get the ptr to the player
    //return (player->getSteps() == board->getMaxSteps() || )

}