#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "model.h"
// controller du MVC : donne les mouvements au model en fct des entrées de l'utilisateur


class Controller{
    shared_ptr<Board> board;
public:
    Controller(shared_ptr<Board> board);
    void move_request();
};

#endif