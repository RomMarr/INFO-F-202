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
    shared_ptr<Player> player = (*board).get_player();
    tuple<int, int>actual_pos = (*player).getPos();
    
    switch (key_event) {
             // REF https://www.fltk.org/doc-1.3/group__fl__events.html#ga12be48f03872da009734f557d1e761bc           
        case FL_Up:
            if (check_move(make_tuple(0,-1))){
                std::cout << "coucou"<<endl;
                (*player).setPos(make_tuple(get<0>(actual_pos),get<1>(actual_pos) - 1));
                break;
            };
        case FL_Down:
            (*player).setPos(make_tuple(get<0>(actual_pos),get<1>(actual_pos) + 1));
            break;

        case FL_Right:
            (*player).setPos(make_tuple(get<0>(actual_pos) + 1,get<1>(actual_pos)));
            break;

        case FL_Left:
            (*player).setPos(make_tuple(get<0>(actual_pos) - 1,get<1>(actual_pos)));
            break;
        
        default:
            break;
    }
}


bool Controller::check_move(tuple<int, int> move){
    std::cout<<"ici ? "<< get<0>(move)<< get<1>(move)<<endl;
    tuple<int, int> posPlayer = (*board).get_player()->getPos();
    std::cout<<get<0>(posPlayer)<< get<1>(posPlayer)<<endl;
    tuple<int, int> new_pos = make_tuple(get<0>(posPlayer) + get<0>(move),get<1>(posPlayer)+get<1>(move));
    cout<< get<0>(new_pos)<<get<1>(new_pos)<<endl;
    std::cout << board->get_box_on_pos <<endl;
    if (board->get_box_on_pos(new_pos)->getType() == Block::BlockType::wall){return false;}
    else {return true;}
}

bool Controller::check_end(){

}