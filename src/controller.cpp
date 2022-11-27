#include "controller.hpp"
#include "model.hpp"

#include <FL/Fl.H>
#include <memory>
#include <tuple>

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
            (*player).setPos(make_tuple(get<0>(actual_pos),get<1>(actual_pos) - 1));
            break;
        
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