#ifndef _POINT_H
#define _POINT_H

class Point{
    int posX;  // coordinate X
    int posY;  // coordinate Y
public:
    Point(int posX, int posY);
    Point();
    void setPosX(int new_posX);
    void setPosY(int new_posY);
    int getPosX();
    int getPosY();
    bool operator==(Point &other);         // compare if the two points have the same coordinates
    bool operator!=(Point &other);         // compare if the two points have different coordinates
    Point operator-(Point &other);         // do the - operation separatly for posX and posY
    Point operator+(const Point &other);   // do the + operation separatly for posX and posY
};

#endif