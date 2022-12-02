#ifndef _PLAYER_H
#define _PLAYER_H

#include "block.hpp"
#include "model.hpp"
// #include "view.hpp"
#include "stdio.h"
#include <string>
#include <memory>
#include <vector>
#include <tuple>


using namespace std;

class Player{
    Point position;              // position in the matrix
    Point move_asked;            // point to add to the position of the player
    int steps = 0;               // number of steps the player has done
    int weight = 0;              // weight of the boxes the player is pushing
    bool teleported = false;     // true if the player use a teleporter
public:
    Player(Point position);
    void setPos(Point new_pos);  
    void setWeight(int new_weight);
    void setMoveAsked(Point new_move_asked);
    void addStep();                // add a step to steps
    void changeTeleported();       // change de boolean of teleprted
    int getSteps();
    int getWeight();
    bool isTeleported(); 
    Point getPos();          
    Point getMoveAsked();
};

#endif