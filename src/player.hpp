#ifndef _PLAYER_H
#define _PLAYER_H

#include "block.hpp"
// #include "view.hpp"
#include "stdio.h"
#include <string>
#include <memory>
#include <vector>
#include <tuple>


using namespace std;

class Player{
    tuple<int, int> position;    // position in the matrix
    tuple<int, int> move_asked;  // tuple to add to the position of the player 
    int steps = 0;               // number of steps the player has done
    int weight = 0;              // weight of the boxes the player is pushing
    bool teleported = false;     // true if the player use a teleporter
public:
    Player(tuple<int, int> position);
    void setPos(tuple<int, int> new_pos);  
    void setWeight(int new_weight);
    void setMoveAsked(tuple<int, int> new_move_asked);
    void addStep();                // add a step to steps
    void changeTeleported();       // change de boolean of teleprted
    tuple<int, int> getPos();
    int getSteps();
    int getWeight();
    bool isTeleported();           
    tuple<int, int> getMoveAsked();
};

#endif