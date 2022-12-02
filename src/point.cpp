#include "point.hpp"

Point::Point(int posX, int posY): posX{posX}, posY{posY} {};

Point::Point(): posX{0}, posY{0} {};

int Point::getPosX(){
    return posX;
}

int Point::getPosY(){
    return posY;
}

void Point::setPosX(int new_posX){
    posX = new_posX;
}

void Point::setPosY(int new_posY){
    posY = new_posY;
}

bool Point::operator==(Point &other){
    return (posX == other.posX && posY == other.posY);
}

bool Point::operator!=(Point &other){
    return (posX != other.posX && posY != other.posY);
}

Point Point::operator+(Point &other){
    int new_posX = posX + other.posX;
    int new_posY = posY + other.posY;
    Point new_point(new_posX, new_posY);
    return new_point;
}

Point Point::operator+(const Point &other){
    int new_posX = posX + other.posX;
    int new_posY = posY + other.posY;
    Point new_point(new_posX, new_posY);
    return new_point;
}