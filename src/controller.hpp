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
    void moveHandler(Point move);  // handle every move after being called by the key_handler
    bool checkMove(Point move);     // check if the move is authorized 
    bool checkLose();                        // check if the player has lost the level
    bool checkWin();                         // check if the player has win the level
    bool isBlocked(shared_ptr<Block> box);   // check if the box can still be moved
    bool failureDetection();                 // check if all the boxes can still be moved
};

#endif