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
                (*player).setPos(make_tuple(get<0>(actual_pos),get<1>(actual_pos) - 1));
                break;
            }; break;
        case FL_Down:
            player->setMoveAsked(make_tuple(0,1));
            if (check_move(make_tuple(0,1))){
                (*player).setPos(make_tuple(get<0>(actual_pos),get<1>(actual_pos) + 1));
                break;
            }; break;
        case FL_Right:
            player->setMoveAsked(make_tuple(1,0));
            if (check_move(make_tuple(1,0))){
                (*player).setPos(make_tuple(get<0>(actual_pos) + 1,get<1>(actual_pos)));
                break;
            }; break;
        case FL_Left:
            player->setMoveAsked(make_tuple(-1,0));
            if (check_move(make_tuple(-1,0))){
                (*player).setPos(make_tuple(get<0>(actual_pos) - 1,get<1>(actual_pos)));
                break;
            }; break;
        default:
            break;
    }player->setWeight(0);
}


bool Controller::check_move(tuple<int, int> move){
    shared_ptr<Player> player = board->get_player();
    tuple<int, int> posPlayer = player->getPos();
    tuple<int, int> new_pos = make_tuple(get<0>(posPlayer) + get<0>(move),get<1>(posPlayer)+get<1>(move));
    if ((get<0>(new_pos)<0 || get<0>(new_pos)>= board->get_width()) || (get<1>(new_pos)<0 || get<1>(new_pos)>= board->get_height())) {
        cout << "en dehors map" <<endl;
        return false;
    }
    if (player->getWeight()>= 10) {
        cout << "trop lourd"<<endl;
        return false;
    }
    if (board->get_block(new_pos)->getType() == Block::BlockType::wall) {
        cout << "mur"<<endl;
        return false;
    } else if (board->get_block(new_pos)->getType()== Block::BlockType::floor){
        shared_ptr<Block> block_on_move = board->get_box_on_pos(new_pos);
       if (block_on_move){
            cout << "a ptr" <<endl;
            player->setWeight(player->getWeight()+block_on_move->getWeight());
            cout << "nv poids : "<<player->getWeight()<<endl;
            if (check_move(make_tuple(get<0>(move)+get<0>(player->getMoveAsked()), get<1>(move)+get<1>(player->getMoveAsked())))){
                cout << "rec"<<endl;
                if (player->getWeight()>= 10) return false;
                else return true;
            }else return false;
                
        }
        
        cout << "no ptr" << endl;
        return true;

    } else if (board->get_block(new_pos)->getType()== Block::BlockType::target){

    } else if (board->get_block(new_pos)->getType()== Block::BlockType::teleporter){

    } else return false;
}

bool Controller::check_end(){

}