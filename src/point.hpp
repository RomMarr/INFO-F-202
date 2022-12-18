#ifndef _POINT_H
#define _POINT_H

#include <iostream>

class Point{
    float posX;  // coordinate X
    float posY;  // coordinate Y
public:
    Point(float posX, float posY);
    Point(int posX, int posY);
    Point();
    void setPosX(float new_posX);
    void setPosY(float new_posY);
    float getPosX();
    float getPosY();
    bool operator==(const Point &other);         // compare if the two points have the same coordinates
    bool operator!=(const Point &other);         // compare if the two points have different coordinates
    Point operator-(const Point &other);         // do the - operation separatly for posX and posY
    Point operator+(const Point &other);         // do the + operation separatly for posX and posY
    Point operator*(const float multiplicator);
    friend std::ostream& operator<<(std::ostream& os, const Point& point);
};

#endif