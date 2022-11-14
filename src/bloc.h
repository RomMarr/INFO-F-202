#ifndef _BLOC_H
#define _BLOC_H

#include "stdio.h"
#include <string>

using namespace std;


class Bloc {
    int weight;
    string color;
public:
    Bloc() ;
    virtual void draw();
    virtual void setWeight(int weight);
    virtual void setColor(string color);
    //~Bloc()
};

class Target:public Bloc{
    int weight;
    string color;
public:
    Target();
    void draw();
    void setWeight(int weight) ;
    void setColor(string color) ;//override ?
    //~Target()
};

class Wall:public Bloc{
    int weight;
    string color;
public:
    Wall();
    void draw();
    void setWeight(int weight) ;
    void setColor(string color); //override ?
    //~Wall()
};

class Floor:public Bloc{
    int weight;
    string color;
public:
    Floor();
    void draw();
    void setWeight(int weight) ;
    void setColor(string color); //override ?
    //~Floor()
};

class Box:public Bloc{
    int weight;
    string color;
public:
    Box();
    void draw();
    void setWeight(int weight) ;
    void setColor(string color); //override ?
    void move();
    //~Box()
};

class Teleporter:public Bloc{
    int weight;
    string color;
public:
    Teleporter();
    void draw();
    void setWeight(int weight) ;
    void setColor(string color); //override ?
    void teleport();
};

#endif