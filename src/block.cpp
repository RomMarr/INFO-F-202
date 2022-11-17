#include "block.h"
#include <FL/Fl.H>


Block::Block(int weight, Fl_Color color):weight{weight}, color{color}{};

void Block::draw(int x, int y) {
};

void Block::setWeight(int new_weight){
    weight = new_weight; };

void Block::setColor(Fl_Color new_color){
    color = new_color; };
