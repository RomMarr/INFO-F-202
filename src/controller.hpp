#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "model.hpp"
#include "block.hpp"
#include "point.hpp"

#include <FL/Fl.H>
#include <memory>
#include <tuple>


class Controller {
    shared_ptr<Board> board;
public:
    Controller(shared_ptr<Board> board);
    void selectLevel(int level_id);          // level selector
    void keyHandler(int key_event);          // handle the event of using the keyboard's keys 
    void moveHandler(const Point &move);     // handle every move after being called by the key_handler
    void animationHandler();                 // called by every redraw of the interface to animate the movement
};

#endif