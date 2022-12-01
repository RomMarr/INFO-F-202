#include "player.hpp"

#include <iostream>
#include <fstream>


Player::Player(tuple<int, int> position): position{position} {};

void Player::setPos(tuple<int, int> new_pos){
    position = new_pos;
}

void Player::setWeight(int new_weight){
    weight = new_weight;
}

void Player::setMoveAsked(tuple<int, int> new_move_asked){
    move_asked = new_move_asked;
}

void Player::addStep(){
    steps += 1;
}

void Player::changeTeleported(){
    teleported = (!teleported);
}

tuple<int, int> Player::getPos(){
    return position;
}

tuple<int, int> Player::getMoveAsked(){
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