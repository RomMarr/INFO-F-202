#include "block.hpp"

#include "constants.hpp"
#include "model.hpp"

#include <FL/Fl.H>


Block::Block(BlockType type): type{type} {
    if (type == BlockType::box) {
        this->setWeight(9);
    } else if (type == BlockType::light_box) {
        this->setWeight(3);
    }
}

void Block::setWeight(int new_weight){
    weight = new_weight; 
}

void Block::setType(BlockType new_type){
    type = new_type;
}

void Block::setPos(Point new_position){
    pos = new_position;
}

Point Block::getPos(){
    return pos;
}

int Block::getWeight(){
    return weight;
}

int Block::getWidth(){
    return width;
}

int Block::getHeight(){
    return height;
}

Fl_Color Block::getColor(){
    switch (type) {
        case (BlockType::wall): return BLOCK_WALL_COLOR; break;
        case (BlockType::box): return BLOCK_BOX_COLOR; break;
        case (BlockType::light_box): return BLOCK_LIGHT_BOX_COLOR; break;
        case (BlockType::floor): return BLOCK_FLOOR_COLOR;  break;
        case (BlockType::target): return BLOCK_TARGET_COLOR; break;
        case (BlockType::teleporter): return fl_rgb_color(153, 0, 153); break;
        default: return fl_rgb_color(100, 100, 100); break;
    }
}

Block::BlockType Block::getType(){
    return type;
}