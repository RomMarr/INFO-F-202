#ifndef _POINT_H
#define _POINT_H

class Point{
    int posX;
    int posY;
public:
    Point(int posX, int posY);
    Point();
    void setPosX(int new_posX);
    void setPosY(int new_posY);
    int getPosX();
    int getPosY();
    bool operator==(Point &other);
    bool operator!=(Point &other);
    Point operator-(Point &other);
    Point operator+(const Point &other);
};

#endif