#ifndef _BLOCK_H
#define _BLOCK_H

#include "point.hpp"
#include "animation.hpp"

#include "stdio.h"
#include <FL/Fl.H>
#include <string>
#include <memory>
#include <vector>
#include <tuple>

using namespace std;


class Block {
public:
    enum BlockType { wall, floor, target, heavy_box, light_box, teleporter }; 
private:    
    BlockType type;         // type of the block   
    int weight;             // weight du block
    int id_color = 0;       // id of the color (0 or 1)
    Point pos;              // position of the block
    Animation animation;    // to allow the boxes' animation
public:
    Block(BlockType type);
    void setWeight(int weight);
    void setType(BlockType new_type);
    void setIdColor(int new_id_color);
    void setPos(Point new_position);
    Point &getPos();
    int getWeight();
    int getIdColor();
    Animation &getAnimation();
    Fl_Color getColor();  // return the color that matches the type 
    BlockType &getType();
};

#endif