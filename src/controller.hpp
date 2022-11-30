#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "model.hpp"
#include "block.hpp"

#include <FL/Fl.H>
#include <memory>
#include <tuple>
// controller du MVC : donne les mouvements au model en fct des entrées de l'utilisateur


class Controller {
    shared_ptr<Board> board;                  // shared ptr to the board (in model)
public:
    Controller(shared_ptr<Board> board);      // constructor
    void select_level(int level_id);          // selector of level 
    void key_handler(int key_event);          // handle the event of using some of the keyboard's keys 
    void move_handler(tuple<int, int> move);  // handle every move after being called by the key_handler
    bool check_move(tuple<int,int> move);     // check if the move is authorized 
    bool check_lose();                        // check if the player has lost the level
    bool check_win();                         // check if the player has win the level
    bool isBlocked(shared_ptr<Block> box);    // check if the box can still be moved
    bool failure_detection();                 // check if all the boxes can still be moved
};

#endif