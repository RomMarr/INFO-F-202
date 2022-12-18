#include "point.hpp"

#include <iostream>

Point::Point(float posX, float posY): posX{posX}, posY{posY} {};

Point::Point(int posX, int posY): posX{static_cast<float>(posX)}, posY{static_cast<float>(posY)} {};

Point::Point(): posX{0}, posY{0} {};

float Point::getPosX(){
    return posX;
}

float Point::getPosY(){
    return posY;
}

void Point::setPosX(float new_posX){
    posX = new_posX;
}

void Point::setPosY(float new_posY){
    posY = new_posY;
}

bool Point::operator==(const Point &other){
    return (posX == other.posX && posY == other.posY);
}

bool Point::operator!=(const Point &other){
    return (posX != other.posX || posY != other.posY);
}

Point Point::operator-(const Point &other){
    float new_posX = posX - other.posX;
    float new_posY = posY - other.posY;
    Point new_point(new_posX, new_posY);
    return new_point;
}

Point Point::operator+(const Point &other){
    float new_posX = posX + other.posX;
    float new_posY = posY + other.posY;
    Point new_point(new_posX, new_posY);
    return new_point;
}

Point Point::operator*(const float multiplicator){
    float new_posX = posX * multiplicator;
    float new_posY = posY * multiplicator;
    Point new_point(new_posX, new_posY);
    return new_point;
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << "(" << std::to_string(point.posX) << ";" << std::to_string(point.posY) << ")";
    return os;
}