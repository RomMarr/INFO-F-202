#include "player.hpp"
#include "point.hpp"

#include <iostream>
#include <fstream>

Player::Player(Point position): position{position} {};

void Player::setPos(Point new_pos){
    position = new_pos;
}

void Player::setWeight(int new_weight){
    weight = new_weight;
}

void Player::setMoveAsked(Point new_move_asked){
    move_asked = new_move_asked;
}

void Player::addStep(){ 
    steps += 1;
}

void Player::changeTeleported(){
    teleported = (!teleported); // change the boolean of teleported
}

Point Player::getPos(){
    return position;
}

Point Player::getMoveAsked(){
    return move_asked;
}

int Player::getSteps(){
    return steps;
}

int Player::getWeight(){
    return weight;
}

bool Player::isTeleported(){
    return teleported;
}