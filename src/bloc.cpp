#include "bloc.h"
#include <FL/Fl.H>


Bloc::Bloc(int weight, Fl_Color color):weight{weight}, color{color}{};

void Bloc::draw() {
};

void Bloc::setWeight(int new_weight){
    weight = new_weight; };

void Bloc::setColor(Fl_Color new_color){
    color = new_color; };
