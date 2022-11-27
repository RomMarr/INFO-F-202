#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "model.hpp"
#include <FL/Fl.H>
// controller du MVC : donne les mouvements au model en fct des entrées de l'utilisateur


class Controller{
    shared_ptr<Board> board;
public:
    Controller(shared_ptr<Board> board);
    void move_request();
    void key_handler(int key_event);
};



#endif