#ifndef _BLOCK_H
#define _BLOCK_H

#include "point.hpp"

#include "stdio.h"
#include <FL/Fl.H>
#include <string>
#include <memory>
#include <vector>
#include <tuple>

using namespace std;


class Block {
public:
    enum BlockType { wall, floor, target, heavy_box, light_box, teleporter }; // peut ajouter Block pour extérieur si on veut
private:    
    const int width = 50;   // wifth of the block
    const int height = 50;  // height of the block 
    BlockType type;         // type of the block   
    int weight;             // weight du block
    int id_color;           // id of the color (between 0 and 3)
    Point pos;              // position of the block
public:
    Block(BlockType type);
    void setWeight(int weight);
    void setType(BlockType new_type);
    void setIdColor(int new_id_color);
    void setPos(Point new_position);
    Point getPos();
    int getWeight();
    int getWidth();
    int getHeight();
    Fl_Color getColor();
    BlockType getType();
};

#endif