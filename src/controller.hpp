#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "model.hpp"
#include "block.hpp"

#include <FL/Fl.H>
#include <memory>
#include <tuple>
// controller du MVC : donne les mouvements au model en fct des entrées de l'utilisateur


class Controller {
    shared_ptr<Board> board;
public:
    Controller(shared_ptr<Board> board);
    void select_level(int level_id);
    void key_handler(int key_event);
    void move_handler(tuple<int, int> move);
    bool check_move(tuple<int,int> move);
    bool check_lose();
    bool check_win();
    bool isBlocked(shared_ptr<Block> box);
    bool failure_detection();
};

#endif