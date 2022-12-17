#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "model.hpp"
#include "block.hpp"
#include "point.hpp"

#include <FL/Fl.H>
#include <memory>
#include <tuple>


class Controller {
    shared_ptr<Board> board;                 // shared ptr to the board (in model)
public:
    Controller(shared_ptr<Board> board);     // constructor
    void selectLevel(int level_id);          // selector of level 
    void keyHandler(int key_event);          // handle the event of using some of the keyboard's keys 
    void moveHandler(const Point &move);     // handle every move after being called by the key_handler
};

#endif