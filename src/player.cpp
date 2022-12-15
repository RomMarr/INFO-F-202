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

void Player::setPositionFrom(Point new_from) {
    position_from = new_from;
}

void Player::addStep(){ 
    steps += 1;
}

void Player::changeTeleported(){
    teleported = (!teleported); // change the boolean of teleported
}

void Player::setMoveAnimation(Point new_move_animation) {
    move_animation = new_move_animation;
}

void Player::setAnimated(bool new_value) {
    animated = new_value;
}

Point Player::getPos(){
    return position;
}

Point Player::getMoveAsked(){
    return move_asked;
}

Point Player::getMoveAnimation(){
    return move_animation;
};

Point Player::getPositionFrom() {
    return position_from;
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

bool Player::isAnimated(){
    return animated;
}