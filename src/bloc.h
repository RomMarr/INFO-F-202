#ifndef _BLOC_H
#define _BLOC_H

#include "stdio.h"
#include <string>
#include <FL/Fl.H>

using namespace std;


class Bloc {
    int weight;
    Fl_Color color;
public:
    Bloc(int weight, Fl_Color color) ;
    void draw();
    void setWeight(int weight);
    void setColor(Fl_Color color);
    ~Bloc();
};

#endif